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
#include "cmsis_os2.h"
#include "motor_control.h"
#include "FreeRTOS.h"
#include "task.h"
#include "sl_hal_timer.h"
#include "sl_device_peripheral.h"

#include "SimpleFOC.h"
#include "motor_control_framework_config.h"

#if ENABLE_BLE
#include "ble_stream_adapter.h"
#endif

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/
#define MC_TASK_FREQUENCY_HZ            5000      // [Hz]: MC task frequency
#define MC_TASK_STACK_SIZE              4096
#define MC_TASK_PRIO                    osPriorityRealtime5
#define MC_TASK_TIMER_PERIPHERAL        SL_PERIPHERAL_TIMER3

#define IO_TASK_DELAY_MS                1
#define IO_TASK_STACK_SIZE              1024
#define IO_TASK_PRIO                    osPriorityNormal

#define VELOCITY_LOOP_DOWNSAMPLE        5

#define DRIVER_PWM_FREQ_HZ              20000     // [Hz]: PWM frequency
#define DRIVER_DEAD_ZONE                0.0f      // (DRV8305 has built in deadzone config)
#define DRIVER_PSU_VOLTAGE_V            24.0f     // [V]: power supply voltage
#define DRIVER_VOLTAGE_LIMIT_V          12.0f     // [V]: Hard limit on output voltage, in volts. Effectively limits PWM duty cycle proportionally to power supply voltage.
#define MOTOR_VELOCITY_LIMIT_RAD_S      530.0f    // [rad/s]: Motor velocity limit.
/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/
static BLDCMotor *motor_p;
static Commander *commander_p;
static HallSensor *sensor_p;

static bool is_mc_ready = false;

// Task handles
static TaskHandle_t xHandle_mc = NULL;
static TaskHandle_t xHandle_io = NULL;

// Task buffers
static StaticTask_t xTaskBuffer_mc;
static StaticTask_t xTaskBuffer_io;
static StackType_t  xStack_mc[MC_TASK_STACK_SIZE];
static StackType_t  xStack_io[IO_TASK_STACK_SIZE];
/*******************************************************************************
 *********************   LOCAL FUNCTION PROTOTYPES   ***************************
 ******************************************************************************/

static void motor_control_task(void *arg);
static void io_task(void *arg);
/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/
void doMotor(char* cmd)
{
  if (!commander_p) {
    return;
  }
  commander_p->motor(motor_p, cmd);
}

void doA()
{
  sensor_p->handleA();
}
void doB()
{
  sensor_p->handleB();
}
void doC()
{
  sensor_p->handleC();
}
/***************************************************************************//**
 * Initialize Hall Sensor Velocity 6PWM example.
 ******************************************************************************/
void motor_control_init(void)
{
  xHandle_io = xTaskCreateStatic(io_task,
                                 "io task",
                                 IO_TASK_STACK_SIZE,
                                 ( void * ) NULL,
                                 IO_TASK_PRIO,
                                 xStack_io,
                                 &xTaskBuffer_io);
  EFM_ASSERT(xHandle_io != NULL);

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
    timer_top = timer_frequency / MC_TASK_FREQUENCY_HZ;

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
 * Hall Sensor Velocity 6PWM task.
 ******************************************************************************/
static void motor_control_task(void *arg)
{
  (void)&arg;

  // Serial uses RTT so baudrate is ignored
  Serial.begin(0);
  SimpleFOCDebug::enable(&Serial);

  Serial.println("Hall Sensor Velocity 6PWM example");

  // driver setup
  static BLDCDriver6PWM driver(PWM_1H, PWM_1L, PWM_2H, PWM_2L, PWM_3H, PWM_3L, PWM_EN);
  // power supply voltage [V]
  driver.voltage_power_supply = DRIVER_PSU_VOLTAGE_V;
  // pwm frequency to be used [Hz]
  driver.pwm_frequency = DRIVER_PWM_FREQ_HZ; // 20 kHz
  // Max DC voltage allowed - default voltage_power_supply
  driver.voltage_limit = DRIVER_VOLTAGE_LIMIT_V;
  // dead zone percentage of the duty cycle - default 0.02 - 2%
  // Can set value to 0 because the DRV8305 will provide the
  // required dead-time.
  driver.dead_zone = DRIVER_DEAD_ZONE;

  if (!driver.init()) {
    Serial.println("Driver init failed!");
    return;
  }

  driver.enable();

  //sensor setup
  static HallSensor sensor(HALL_A, HALL_B, HALL_C, MOTOR_PP);
  sensor.init();

  sensor_p = &sensor;

  sensor.enableInterrupts(doA, doB, doC);

  //motor setup
  static BLDCMotor motor(MOTOR_PP);
  motor.linkDriver(&driver);
  motor.linkSensor(&sensor);

  // Set below the motor's max velocity limit
  motor.velocity_limit = MOTOR_VELOCITY_LIMIT_RAD_S;
  // set motion control loop to be used
  motor.controller = MotionControlType::velocity;
  // choose FOC modulation (optional) - SinePWM or SpaceVectorPWM
  motor.foc_modulation = FOCModulationType::SpaceVectorPWM;
  // controller configuration
  // velocity PI controller parameters
  motor.PID_velocity.P = 0.05f;
  motor.PID_velocity.I = 0.4f;
  // velocity low pass filtering time constant
  motor.LPF_velocity.Tf = 0.01f;

#if ENABLE_MONITOR
  motor.useMonitoring(Serial);
  motor.monitor_variables = _MON_TARGET | _MON_CURR_Q | _MON_CURR_D | _MON_VEL;
#endif

  if (!motor.init()) {
    Serial.println("Motor init failed!");
    return;
  }

  // commander setup
  static Commander commander(Serial);
  commander_p = &commander;
  commander.add('M', doMotor, "motor");

  if (!motor.initFOC()) {
    Serial.println("FOC init failed!");
    return;
  }

  motor_p = &motor;

  Serial.println("Motor ready!");
  Serial.println("Set target velocity [rad/s]");

  sl_interrupt_manager_set_irq_priority(TIMER3_IRQn, 3);
  sl_interrupt_manager_enable_irq(TIMER3_IRQn);
  sl_hal_timer_enable_interrupts((TIMER_TypeDef *)MC_TASK_TIMER_PERIPHERAL->base, TIMER_IF_OF);
  sl_hal_timer_start((TIMER_TypeDef *)MC_TASK_TIMER_PERIPHERAL->base);

  is_mc_ready = true;
  uint32_t foc_tick = 0;

  while (1) {
    xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);
    motor_p->loopFOC();
    if (++foc_tick >= VELOCITY_LOOP_DOWNSAMPLE) {
      foc_tick = 0;
      motor_p->move();
    }
  }
}

static void io_task(void *arg)
{
  (void)&arg;

  while (1) {
    if (is_mc_ready) {
#if ENABLE_MONITOR
      motor_p->monitor();
#endif
      commander_p->run();
#if ENABLE_BLE
      commander_p->run(bleStreamAdapter);
      bleStreamAdapter.flushTx();
#endif
    }
    vTaskDelay(pdMS_TO_TICKS(IO_TASK_DELAY_MS));
  }
}

void TIMER3_IRQHandler(void)
{
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  sl_hal_timer_clear_interrupts((TIMER_TypeDef *)MC_TASK_TIMER_PERIPHERAL->base, TIMER_IF_OF);
  xTaskNotifyFromISR(xHandle_mc, 0, eNoAction, &xHigherPriorityTaskWoken);
  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
