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

#define DRIVER_PWM_FREQ_HZ              20000     // [Hz]: PWM frequency
#define DRIVER_DEAD_ZONE                0.0f      // (DRV8305 has built in deadzone config)
#define DRIVER_PSU_VOLTAGE_V            24.0f     // [V]: power supply voltage
#define DRIVER_VOLTAGE_LIMIT_V          12.0f     // [V]: Hard limit on output voltage, in volts. Effectively limits PWM duty cycle proportionally to power supply voltage.
#define MOTOR_VOLTAGE_LIMIT_V           12.0f     // [V]: Global voltage limit. Limits Q-axis voltage.
#define MOTOR_VELOCITY_LIMIT_RPM        530.0f    // [RPM]: Motor velocity limit.
/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/
static BLDCMotor *motor_p;
static HallSensor *sensor_p;
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

  // Set below the motor's max 5600 RPM limit = 586 rad/s
  motor.velocity_limit = MOTOR_VELOCITY_LIMIT_RPM;
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
  motor.PID_current_q.I = 50.0f;
  motor.LPF_current_q.Tf = 0.05f;

  // current d loop PID
  motor.PID_current_d.P = 1.0f;
  motor.PID_current_d.I = 50.0f;
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
  static Commander commander(Serial);
  commander_p = &commander;
  commander.add('M', doMotor, "motor");

  // Current Sense
  static LowsideCurrentSense current_sense(DRIVER_SHUNT_RESISTANCE, DRIVER_SHUNT_GAIN, CURR_SEN_A, CURR_SEN_B, CURR_SEN_C);

  current_sense.linkDriver(&driver);

  if (!current_sense.init()) {
    Serial.println("Current Sense init failed!");
    return;
  }

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
    motor.monitor();
#endif

    // user communication
    commander.run();

    vTaskDelay(xDelay);
  }
}

#endif // APPLICATION_EXAMPLE == EXAMPLE_TORQUE_VELOCITY_6PWM
