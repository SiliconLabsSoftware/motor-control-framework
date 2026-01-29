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

#if APPLICATION_EXAMPLE == EXAMPLE_TORQUE_VELOCITY_6PWM

#include "motor_control.h"
#include "FreeRTOS.h"
#include "task.h"

#include "../../external/simplefoc/src/SimpleFOC.h"

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
 * Initialize Torque Sensor Velocity 6PWM example.
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

  Serial.println("Torque Sensor Velocity 6PWM example");

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
  // set torque mode
  motor.torque_controller = TorqueControlType::foc_current;

  // controller configuration
  // velocity PI controller parameters
  motor.PID_velocity.P = 0.025f;
  motor.PID_velocity.I = 0.4;
  // velocity low pass filtering time constant
  motor.LPF_velocity.Tf = 0.01f;

  // current q loop PID
  motor.PID_current_q.P = 1.0f;
  motor.PID_current_q.I = 100.0f;
  motor.LPF_current_q.Tf = 0.05f;

  // current d loop PID
  motor.PID_current_d.P = 1.0f;
  motor.PID_current_d.I = 100.0f;
  motor.LPF_current_d.Tf = 0.05f;

  motor.target = 0.0f;

#if ENABLE_MONITOR
  motor.useMonitoring(Serial);
  motor.monitor_variables = _MON_TARGET | _MON_CURR_Q | _MON_CURR_D | _MON_VEL | _MON_ANGLE;
#endif

  if (!motor.init()) {
    Serial.println("Motor init failed!");
    return;
  }

  // commander setup
  static Commander command(Serial);
  command_p = &command;
  command.add('M', doMotor, "motor");

  // Current Sense
  static LowsideCurrentSense current_sense(0.007f, 10.0f, CURR_SEN_A, CURR_SEN_B, CURR_SEN_C);
  current_sense_p = &current_sense;

  current_sense.linkDriver(&driver);

  if (!current_sense.init()) {
    Serial.println("Current Sense init failed!");
    return;
  }

  // DRV8305 has inverted gains on all channels
  // current_sense.gain_a *= -1;
  // current_sense.gain_b *= -1;
  // current_sense.gain_c *= -1;

  // link the motor and the driver
  motor.linkCurrentSense(&current_sense);

  if (!motor.initFOC()) {
    Serial.println("FOC init failed!");
    return;
  }

  motor_p = &motor;

  Serial.println("Motor ready!");
  Serial.println("Set target velocity [rad/s]");

  vTaskDelay(1000 / portTICK_PERIOD_MS);

  while (1) {
    // main FOC algorithm function
    // the faster you run this function the better
    motor.loopFOC();

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

    // user communication
    command.run();

    vTaskDelay(xDelay);
  }
}

#endif // APPLICATION_EXAMPLE == EXAMPLE_CUSTOM
