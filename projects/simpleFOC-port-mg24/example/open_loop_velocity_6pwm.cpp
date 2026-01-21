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
#include "device_config.h"

#if APPLICATION_EXAMPLE == EXAMPLE_OPEN_LOOP_VELOCITY_6PWM

#include "motor_control.h"
#include "FreeRTOS.h"
#include "task.h"

#include "../external/simplefoc/src/SimpleFOC.h"

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
/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/
BLDCMotor *motor_p;
BLDCDriver6PWM *driver_p;
Commander *command_p;
/*******************************************************************************
 *********************   LOCAL FUNCTION PROTOTYPES   ***************************
 ******************************************************************************/

static void motor_control_task(void *arg);

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
/***************************************************************************//**
 * Initialize blink example.
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
  driver.voltage_power_supply = 24;
  // pwm frequency to be used [Hz]
  driver.pwm_frequency = 20000; // 20 kHz
  // Max DC voltage allowed - default voltage_power_supply
  driver.voltage_limit = 12;
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

  //motor setup
  static BLDCMotor motor(MOTOR_PP);
  motor.linkDriver(&driver);

  // default voltage_power_supply
  motor.voltage_limit = 0.8f;
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
  static Commander command(Serial);
  command_p = &command;
  command.add('M', doMotor, "motor");

  motor_p = &motor;

  Serial.println("Motor ready!");
  Serial.println("Set target velocity [rad/s]");

  vTaskDelay(1000 / portTICK_PERIOD_MS);

  while (1) {
    motor.move();
#if ENABLE_MONITOR
    motor.monitor();
#endif
    command.run();

    vTaskDelay(xDelay);
  }
}

#endif // APPLICATION_EXAMPLE == EXAMPLE_CUSTOM
