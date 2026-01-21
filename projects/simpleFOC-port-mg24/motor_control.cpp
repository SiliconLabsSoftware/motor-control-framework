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

#if APPLICATION_EXAMPLE == EXAMPLE_CUSTOM

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
HallSensor *sensor_p;
Commander *command_p;
LowsideCurrentSense *current_sense_p;
/*******************************************************************************
 *********************   LOCAL FUNCTION PROTOTYPES   ***************************
 ******************************************************************************/

static void motor_control_task(void *arg);

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/
void doMotor(char* cmd) {
  if (!command_p) return;
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
 * Torque Sensor Velocity 6PWM task.
 ******************************************************************************/
static void motor_control_task(void *arg)
{
  (void)&arg;

  //Use the provided calculation macro to convert milliseconds to OS ticks
  const TickType_t xDelay = pdMS_TO_TICKS(TOOGLE_DELAY_MS);

  // Serial uses RTT so baudrate is ignored
  Serial.begin(0);
  SimpleFOCDebug::enable(&Serial);

  Serial.println("Custom example");

  // TODO: driver setup
  // TODO: (optional) sensor setup
  // TODO: motor setup
  // TODO: (optional) current sense setup

  // commander setup
  static Commander command(Serial);
  command_p = &command;
  command.add('M', doMotor, "motor");

  Serial.println("Commander ready.");

  vTaskDelay(1000 / portTICK_PERIOD_MS);

  while (1) {
    // TODO: motor.loopFOC(); for main FOC algorithm function
    // TODO: motor.move(); for Motion control function

  #if ENABLE_MONITOR
    // TODO: motor.monitor(); for monitoring
  #endif
  
    // user communication
    command.run();

    vTaskDelay(xDelay);
  }
}

#endif // APPLICATION_EXAMPLE == EXAMPLE_CUSTOM
