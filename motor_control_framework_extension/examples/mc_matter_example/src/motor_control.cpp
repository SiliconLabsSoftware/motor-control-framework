/***************************************************************************//**
 * @file
 * @brief Motor control functions
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
 #include "motor_control_framework_config.h"

 #include "cmsis_os2.h"
 #include "motor_control.h"
 #include "sl_hal_timer.h"
 #include "sl_device_peripheral.h"

 #include "SimpleFOC.h"
//Needs to be moved here to avoid build error?
 #include "FreeRTOS.h"
 #include "task.h"
//End of move
 #include "MXLEMMINGObserverSensor.h"
 #include "app_properties_config.h"

 #include <lib/support/logging/CHIPLogging.h>

 #ifdef SL_CATALOG_SYSTEMVIEW_TRACE_PRESENT
 #include "SEGGER_SYSVIEW.h"
 #endif

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/
 #define MC_LOOP_FREQUENCY_HZ            5000     // [Hz]: MC task frequency
 #define MC_TASK_STACK_SIZE              4096
 #define MC_TASK_PRIO                    osPriorityRealtime5
 #define MC_TASK_TIMER_PERIPHERAL        SL_PERIPHERAL_TIMER3

 #define IO_TASK_DELAY_MS                1
 #define IO_TASK_STACK_SIZE              1024
 #define IO_TASK_PRIO                    osPriorityNormal

 #define VELOCITY_LOOP_DOWNSAMPLE        5

 #ifndef CONTROL_LATENCY_MS
 #define CONTROL_LATENCY_MS            10
 #endif

 #define DRIVER_PWM_FREQ_HZ              20000     // [Hz]: PWM frequency
 #define DRIVER_DEAD_ZONE                0.0f      // (DRV8305 has built in deadzone config)
 #define DRIVER_PSU_VOLTAGE_V            24.0f     // [V]: power supply voltage
 #define DRIVER_VOLTAGE_LIMIT_V          12.0f     // [V]: Hard limit on output voltage, in volts. Effectively limits PWM duty cycle proportionally to power supply voltage.
 #define MOTOR_VOLTAGE_LIMIT_V           12.0f     // [V]: Global voltage limit. Limits Q-axis voltage.
 #define MOTOR_CURRENT_LIMIT_A           4.0f      // [A]: Global current limit. Limits Q-axis current.

//#define SENSORLESS_MODE
/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/

static BLDCMotor *motor_p;
static Commander *commander_p;
static BLDCDriver6PWM *driver_p;
#ifndef SENSORLESS_MODE
static HallSensor *sensor_p;
#endif

static float matter_target_speed = 0.0;

// Task handles
static TaskHandle_t xHandle_mc = NULL;

// Task buffers
static StaticTask_t xTaskBuffer_mc;
static StackType_t  xStack_mc[MC_TASK_STACK_SIZE];

/*******************************************************************************
 *********************   LOCAL FUNCTION PROTOTYPES   ***************************
 ******************************************************************************/

static void motor_control_task(void *arg);
/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

#ifndef SENSORLESS_MODE
void doA()
{
  #ifdef SL_CATALOG_SYSTEMVIEW_TRACE_PRESENT
  SEGGER_SYSVIEW_RecordEnterISR();
  #endif

  sensor_p->handleA();

  #ifdef SL_CATALOG_SYSTEMVIEW_TRACE_PRESENT
  SEGGER_SYSVIEW_RecordExitISR();
  #endif
}
void doB()
{
  #ifdef SL_CATALOG_SYSTEMVIEW_TRACE_PRESENT
  SEGGER_SYSVIEW_RecordEnterISR();
  #endif

  sensor_p->handleB();

  #ifdef SL_CATALOG_SYSTEMVIEW_TRACE_PRESENT
  SEGGER_SYSVIEW_RecordExitISR();
  #endif
}
void doC()
{
  #ifdef SL_CATALOG_SYSTEMVIEW_TRACE_PRESENT
  SEGGER_SYSVIEW_RecordEnterISR();
  #endif

  sensor_p->handleC();

  #ifdef SL_CATALOG_SYSTEMVIEW_TRACE_PRESENT
  SEGGER_SYSVIEW_RecordExitISR();
  #endif
}
#endif

/***************************************************************************//**
 * Initialize blink example.
 ******************************************************************************/
void motor_control_init(void)
{
  xHandle_mc = xTaskCreateStatic(motor_control_task,
                                 "motor control task",
                                 MC_TASK_STACK_SIZE,
                                 ( void * ) NULL,
                                 MC_TASK_PRIO,
                                 xStack_mc,
                                 &xTaskBuffer_mc);
  EFM_ASSERT(xHandle_mc != NULL);

  uint32_t timer_frequency;
  uint32_t timer_top = 0xFFFFFFFF;
  uint32_t timer_prescaler = 0;

  sl_clock_manager_enable_bus_clock(MC_TASK_TIMER_PERIPHERAL->bus_clock);
  sl_clock_manager_get_clock_branch_frequency(MC_TASK_TIMER_PERIPHERAL->clk_branch, &timer_frequency);

  while (timer_top > 0xFFFF) {
    timer_top = timer_frequency / MC_LOOP_FREQUENCY_HZ;

    if (timer_top == 0) {
      timer_top = 1;
      break;
    } else if (timer_top > 0xFFFF) {
      timer_frequency /= 2;
      timer_prescaler = (timer_prescaler << 1) | 1;
    } else {
      break;
    }
  }

  sl_hal_timer_init_t timer_init = SL_HAL_TIMER_INIT_DEFAULT;
  timer_init.prescaler = (sl_hal_timer_prescaler_t)timer_prescaler;

  sl_hal_timer_init((TIMER_TypeDef *)MC_TASK_TIMER_PERIPHERAL->base, &timer_init);
  sl_hal_timer_enable((TIMER_TypeDef *)MC_TASK_TIMER_PERIPHERAL->base);
  sl_hal_timer_stop((TIMER_TypeDef *)MC_TASK_TIMER_PERIPHERAL->base);
  sl_hal_timer_set_top((TIMER_TypeDef *)MC_TASK_TIMER_PERIPHERAL->base, timer_top);
  sl_hal_timer_disable_interrupts((TIMER_TypeDef *)MC_TASK_TIMER_PERIPHERAL->base, _TIMER_IF_MASK);
  sl_hal_timer_clear_interrupts((TIMER_TypeDef *)MC_TASK_TIMER_PERIPHERAL->base, _TIMER_IF_MASK);
}

/*******************************************************************************
 * Torque Sensor Velocity 6PWM task.
 ******************************************************************************/
static void motor_control_task(void *arg)
{
  (void)&arg;

  static BLDCMotor motor(MOTOR_PP, MOTOR_RESISTANCE, MOTOR_KV, MOTOR_INDUCTANCE);
  static BLDCDriver6PWM driver(PWM_1H, PWM_1L, PWM_2H, PWM_2L, PWM_3H, PWM_3L, PWM_EN);
  static LowsideCurrentSense current_sense(0.007f, 10.0f, CURR_SEN_A, CURR_SEN_B, CURR_SEN_C);
  static MXLEMMINGObserverSensor observer(motor);
  static Commander commander;//Serial

  motor_p = &motor;
  commander_p = &commander;

  #ifdef SENSORLESS_MODE
  // Link observer as the "sensor"
  motor.linkSensor(&observer);
  #endif

  // Driver setup
  driver.voltage_power_supply = DRIVER_PSU_VOLTAGE_V;
  driver.voltage_limit = DRIVER_VOLTAGE_LIMIT_V;
  driver.pwm_frequency = DRIVER_PWM_FREQ_HZ;
  driver.dead_zone = DRIVER_DEAD_ZONE;

  driver_p = &driver;
  driver.init();
  driver.enable();
  motor.linkDriver(&driver);

  #ifndef SENSORLESS_MODE
  //sensor setup
  static HallSensor sensor(HALL_A, HALL_B, HALL_C, MOTOR_PP);
  sensor.init();
  sensor.enableInterrupts(doA, doB, doC);
  sensor_p = &sensor;

  motor.linkSensor(&sensor);
  #endif

  // Motor setup
  motor.foc_modulation = FOCModulationType::SpaceVectorPWM;
  motor.controller = MotionControlType::velocity;
  motor.torque_controller = TorqueControlType::voltage;

  // Velocity control
  motor.PID_velocity.P = 0.2f;
  motor.PID_velocity.I = 2.0f;
  motor.PID_velocity.D = 0.0f;
  motor.LPF_velocity.Tf = 0.01f;

  motor.current_limit = MOTOR_CURRENT_LIMIT_A;

  VerifyOrDie(motor.init());

  #ifdef SENSORLESS_MODE
  current_sense.linkDriver(&driver);
  current_sense.init();
  motor.linkCurrentSense(&current_sense);
  #endif

  // Sensorless: skip sensor alignment
  motor.sensor_direction = Direction::CW;
  motor.zero_electric_angle = 0.0f;

  VerifyOrDie(motor.initFOC());

  sl_interrupt_manager_set_irq_priority(TIMER3_IRQn, 3);
  sl_interrupt_manager_enable_irq(TIMER3_IRQn);
  sl_hal_timer_enable_interrupts((TIMER_TypeDef *)MC_TASK_TIMER_PERIPHERAL->base, TIMER_IF_OF);
  sl_hal_timer_start((TIMER_TypeDef *)MC_TASK_TIMER_PERIPHERAL->base);

  motor_p->disable();
  motor_p->controller = MotionControlType::velocity;
  const TickType_t xDelay = pdMS_TO_TICKS(CONTROL_LATENCY_MS);
  static float current_target = 0;

  while (1) {
    if (current_target != matter_target_speed) {
      const float step = 1;
      if (abs(current_target - matter_target_speed) < step) {
        current_target = matter_target_speed;
      } else {
        if (matter_target_speed > current_target) {
          current_target += step;
        } else {
          current_target -= step;
        }
      }
    } else {
    }
    if (abs(current_target) < 30) {
      motor_p->disable();
    } else {
      motor_p->enable();
      motor_p->move(current_target);
    }
    vTaskDelay(xDelay);
  }
}

void command_the_motor(uint8_t percent, chip::app::Clusters::FanControl::AirflowDirectionEnum direction)
{
  matter_target_speed = 5.0 * percent;
  if (direction == chip::app::Clusters::FanControl::AirflowDirectionEnum::kReverse) {
    matter_target_speed *= -1;
  }
}

void TIMER3_IRQHandler(void)
{
  #ifdef SL_CATALOG_SYSTEMVIEW_TRACE_PRESENT
  SEGGER_SYSVIEW_RecordEnterISR();
  #endif

  sl_hal_timer_clear_interrupts((TIMER_TypeDef *)MC_TASK_TIMER_PERIPHERAL->base, TIMER_IF_OF);
  motor_p->loopFOC();

  #ifdef SL_CATALOG_SYSTEMVIEW_TRACE_PRESENT
  SEGGER_SYSVIEW_RecordExitISR();
  #endif
}
