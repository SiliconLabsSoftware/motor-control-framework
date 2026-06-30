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
#include "FreeRTOS.h"
#include "task.h"
#include "em_core.h"
#include "em_gpio.h"
#include "sl_hal_timer.h"
#include "sl_device_peripheral.h"
#include "imu_task.h"
#include "ble_stream_adapter.h"

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/
 #define MC_TASK_FREQUENCY_HZ            5000      // [Hz]: MC task frequency
 #define MC_TASK_STACK_SIZE              4096
 #define MC_TASK_PRIO                    osPriorityRealtime5
 #define MC_TASK_TIMER_PERIPHERAL        SL_PERIPHERAL_TIMER3
 #define FAIL_SAFE_ANOMALY_LEVEL        70
 #define ANOMALY_BLANKING_DEFAULT_MS        1000U   // default blanking after setpoint step
 #define TARGET_STEP_THRESH_DEFAULT         5.0f   // rad/s change that triggers blanking

#ifndef TOOGLE_DELAY_MS
#define TOOGLE_DELAY_MS            1
#endif

#ifndef MC_TASK_STACK_SIZE
#define MC_TASK_STACK_SIZE      8192
#endif

#ifndef MC_TASK_PRIO
#define MC_TASK_PRIO            44
#endif
/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/
BLDCMotor *motor_p;
BLDCDriver6PWM *driver_p;
HallSensor *sensor_p;
Commander *command_p;

bool auto_fail_safe = false;

static uint32_t g_anomaly_blanking_ms = ANOMALY_BLANKING_DEFAULT_MS;
static float    g_target_step_thresh  = TARGET_STEP_THRESH_DEFAULT;

static TickType_t g_blank_start_tick  = 0;
static TickType_t g_blank_duration_ticks = 0;
static bool g_blank_active = false;

static float g_last_target = 0.0f;
static bool  g_fault_latched_stop = false;

/*******************************************************************************
 *********************   LOCAL FUNCTION PROTOTYPES   ***************************
 ******************************************************************************/

static void motor_control_task(void *arg);
void receiveCustomCommand(char* data);
void faultShutOff(void);

static inline void anomalyBlankingStart(void);
static inline bool anomalyBlankingActive(void);

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/
void doMotor(char* cmd)
{
  if (!command_p) {
    return;
  }
  command_p->motor(motor_p, cmd);
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
  TaskHandle_t xHandle = NULL;

  static StaticTask_t xTaskBuffer;
  static StackType_t  xStack[MC_TASK_STACK_SIZE];

  xHandle = xTaskCreateStatic(motor_control_task,
                              "motor control task",
                              MC_TASK_STACK_SIZE,
                              ( void * ) NULL,
                              MC_TASK_PRIO,
                              xStack,
                              &xTaskBuffer);

  // Since puxStackBuffer and pxTaskBuffer parameters are not NULL,
  // it is impossible for xHandle to be null. This check is for
  // rigorous example demonstration.
  EFM_ASSERT(xHandle != NULL);

  //init timer for control loop
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

  //Use the provided calculation macro to convert milliseconds to OS ticks
  const TickType_t xDelay = pdMS_TO_TICKS(TOOGLE_DELAY_MS);

  // Serial uses RTT so baudrate is ignored
  Serial.begin(0);
  SimpleFOCDebug::enable(&Serial);

  Serial.println("Hall Sensor Velocity 6PWM example");

  // driver setup
  static BLDCDriver6PWM driver(PWM_1H, PWM_1L, PWM_2H, PWM_2L, PWM_3H, PWM_3L, PWM_EN);
  // power supply voltage [V]
  driver.voltage_power_supply = 24;
  // pwm frequency to be used [Hz]
  driver.pwm_frequency = 20000; // 20 kHz
  // Max DC voltage allowed - default voltage_power_supply
  driver.voltage_limit = 24;
  // dead zone percentage of the duty cycle - default 0.02 - 2%
  // Can set value to 0 because the DRV8305 will provide the
  // required dead-time.
  driver.dead_zone = 0;

  if (!driver.init()) {
    Serial.println("Driver init failed!");
    return;
  }

  driver_p = &driver;

  driver.enable();

  //disable driver chip select
  // Configure PC8 as push-pull output, initial level high
  GPIO_PinModeSet(DRV_SPI_CS_PORT, DRV_SPI_CS_PIN, gpioModePushPull, 1);
  GPIO_PinOutSet(DRV_SPI_CS_PORT, DRV_SPI_CS_PIN);

  //sensor setup
  static HallSensor sensor(HALL_A, HALL_B, HALL_C, MOTOR_PP);
  sensor.init();

  sensor_p = &sensor;

  sensor.enableInterrupts(doA, doB, doC);

  //motor setup
  static BLDCMotor motor(MOTOR_PP);
  motor.linkDriver(&driver);
  motor.linkSensor(&sensor);

  // Set below the motor's max 5600 RPM limit = 586 rad/s
  motor.velocity_limit = 530.0f;
  // set motion control loop to be used
  motor.controller = MotionControlType::velocity;
  // choose FOC modulation (optional) - SinePWM or SpaceVectorPWM
  motor.foc_modulation = FOCModulationType::SpaceVectorPWM;
  // controller configuration
  // velocity PI controller parameters
  motor.PID_velocity.P = 0.05f;
  motor.PID_velocity.I = 1;
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
  static Commander command(Serial);
  command_p = &command;
  // add motor commands
  command.add('M', doMotor, "motor");
  // add anomaly keyword
  command.add('A', receiveCustomCommand, "anomaly");

  if (!motor.initFOC()) {
    Serial.println("FOC init failed!");
    return;
  }

  motor_p = &motor;

  Serial.println("Motor ready!");
  Serial.println("Set target velocity [rad/s]");

  vTaskDelay(1000 / portTICK_PERIOD_MS);

  sl_interrupt_manager_set_irq_priority(TIMER3_IRQn, 3);
  sl_interrupt_manager_enable_irq(TIMER3_IRQn);
  sl_hal_timer_enable_interrupts((TIMER_TypeDef *)MC_TASK_TIMER_PERIPHERAL->base, TIMER_IF_OF);
  sl_hal_timer_start((TIMER_TypeDef *)MC_TASK_TIMER_PERIPHERAL->base);

  while (1) {
    //Check auto shutoff trigger
    faultShutOff();

    // Motion control function
    // velocity, position or voltage (defined in motor.controller)
    // this function can be run at much lower frequency than loopFOC() function
    // You can also use motor.move() and set the motor.target in the code
    motor.move();

  #if ENABLE_MONITOR
    // function intended to be used with serial plotter to monitor motor variables
    // significantly slowing the execution down!!!!
    motor.monitor();
  #endif

    // user communication on BLE
    command.run(bleStreamAdapter);
    // user communication on RTT
    command.run(Serial);

    vTaskDelay(xDelay);
  }
}

void TIMER3_IRQHandler(void)
{
  SEGGER_SYSVIEW_RecordEnterISR();
  sl_hal_timer_clear_interrupts((TIMER_TypeDef *)MC_TASK_TIMER_PERIPHERAL->base, TIMER_IF_OF);
  motor_p->loopFOC();
  SEGGER_SYSVIEW_RecordExitISR();
}

void receiveCustomCommand(char* data)
{
  if (data[0] == 'O' && data[1] == 'F' && data[2] == 'F' ) {  // Auto OFF feature
    if (data[3] == '1') {
      auto_fail_safe = true;                    //Enable auto fail safe
    } else if (data[3] == '0') {
      auto_fail_safe = false;                         //Disable auto fail safe
    } else {
      Serial.print("Wrong auto fail safe attribute!");
    }
  } else {
    Serial.print("Wrong Anomaly data received:");
    Serial.print(data[0]);
    Serial.print(data[1]);
    Serial.println(data[2]);
  }
}

void faultShutOff(void)
{
  float anomaly = 0;

  // If auto fail safe is not enabled, return immediately
  if (!auto_fail_safe) {
    return;
  }

  float tgt = motor_p->target;

  // Detect target step changes and start blanking
  // (Also handles the case where user restarts after a fault stop.)
  if (!g_fault_latched_stop) {
    if (fabsf(tgt - g_last_target) > g_target_step_thresh) {
      anomalyBlankingStart();
      g_last_target = tgt;
    }
  } else {
    // If we were fault-stopped and user sets a non-zero target, allow restart + blanking
    if (fabsf(tgt) > 0.001f) {
      g_fault_latched_stop = false;
      anomalyBlankingStart();
      g_last_target = tgt;
    }
  }

  // Skip anomaly shutoff during blanking window
  if (anomalyBlankingActive()) {
    return;
  }

  anomaly = getAnomaly() * 100;
  if (anomaly > FAIL_SAFE_ANOMALY_LEVEL) {
    motor_p->target = 0;//stop
  }
}

static inline void anomalyBlankingStart(void)
{
  if (g_anomaly_blanking_ms == 0U) {
    g_blank_active = false;
    g_blank_duration_ticks = 0;
    return;
  }
  g_blank_start_tick = xTaskGetTickCount();
  g_blank_duration_ticks = pdMS_TO_TICKS(g_anomaly_blanking_ms);
  g_blank_active = (g_blank_duration_ticks > 0);
}

static inline bool anomalyBlankingActive(void)
{
  if (!g_blank_active) {
    return false;
  }
  TickType_t now = xTaskGetTickCount();
  // Wrap-safe check
  if ((TickType_t)(now - g_blank_start_tick) < g_blank_duration_ticks) {
    return true;
  }
  g_blank_active = false;
  return false;
}
