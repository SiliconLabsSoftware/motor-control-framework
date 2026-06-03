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
#include "motor_control.h"
#include "FreeRTOS.h"
#include "task.h"

#include "SimpleFOC.h"
#include "motor_control_framework_config.h"

#if ENABLE_BLE
#include "ble_stream_adapter.h"
#endif

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/
#ifndef TOOGLE_DELAY_MS
#define TOOGLE_DELAY_MS            1
#endif

#ifndef MC_TASK_STACK_SIZE
#define MC_TASK_STACK_SIZE      8192
#endif

#ifndef MC_TASK_PRIO
#define MC_TASK_PRIO            30
#endif

#define DRIVER_PWM_FREQ_HZ              20000     // [Hz]: PWM frequency
#define DRIVER_DEAD_ZONE                0.0f      // (DRV8305 has built in deadzone config)
#define DRIVER_PSU_VOLTAGE_V            24.0f     // [V]: power supply voltage
#define DRIVER_VOLTAGE_LIMIT_V          12.0f     // [V]: Hard limit on output voltage, in volts. Effectively limits PWM duty cycle proportionally to power supply voltage.
#define MOTOR_VOLTAGE_LIMIT_V           0.8f      // [V]: Global voltage limit. Limits Q-axis voltage.
/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/
static BLDCMotor *motor_p;
static Commander *commander_p;
/*******************************************************************************
 *********************   LOCAL FUNCTION PROTOTYPES   ***************************
 ******************************************************************************/

static void motor_control_task(void *arg);

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
/***************************************************************************//**
 * Initialize Open Loop Velocity 6PWM example.
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
}

/*******************************************************************************
 * Open Loop Velocity 6PWM task.
 ******************************************************************************/
static void motor_control_task(void *arg)
{
  (void)&arg;

  //Use the provided calculation macro to convert milliseconds to OS ticks
  const TickType_t xDelay = pdMS_TO_TICKS(TOOGLE_DELAY_MS);

  // Serial uses RTT so baudrate is ignored
  Serial.begin(0);
  SimpleFOCDebug::enable(&Serial);

  Serial.println("Open Loop Velocity 6PWM example");

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

  //motor setup
  static BLDCMotor motor(MOTOR_PP);
  motor.linkDriver(&driver);

  // default voltage_power_supply
  motor.voltage_limit = MOTOR_VOLTAGE_LIMIT_V;
  // set motion control loop to be used
  motor.controller = MotionControlType::velocity_openloop;
  // choose FOC modulation (optional) - SinePWM or SpaceVectorPWM
  motor.foc_modulation = FOCModulationType::SpaceVectorPWM;

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

  motor_p = &motor;

  Serial.println("Motor ready!");
  Serial.println("Set target velocity [rad/s]");

  vTaskDelay(1000 / portTICK_PERIOD_MS);

  while (1) {
    motor.move();
#if ENABLE_MONITOR
    motor.monitor();
#endif
    commander.run();
#if ENABLE_BLE
    commander.run(bleStreamAdapter);
    bleStreamAdapter.flushTx();
#endif
    vTaskDelay(xDelay);
  }
}
