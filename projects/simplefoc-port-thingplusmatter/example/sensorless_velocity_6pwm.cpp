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

#if APPLICATION_EXAMPLE == EXAMPLE_SENSORLESS_VELOCITY_6PWM

#include "motor_control.h"
#include "FreeRTOS.h"
#include "task.h"

#include "../external/simplefoc/src/SimpleFOC.h"
#include "MXLEMMINGObserverSensor.h"

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

#define LOCKING_DURATION_MS             1000      // [ms]: time spent in locking state before closing the loop
#define OBSERVER_MIN_VELOCITY_TO_LOCK   100.0f    // [rad/s]: min velocity where observer is stable
#define RAMP_ACCELERATION               2.0f      // [rad/s2]: open-loop acceleration

#define DRIVER_PWM_FREQ_HZ              20000     // [Hz]: PWM frequency
#define DRIVER_DEAD_ZONE                0.0f      // (DRV8305 has built in deadzone config)
#define DRIVER_PSU_VOLTAGE_V            24.0f     // [V]: power supply voltage
#define DRIVER_VOLTAGE_LIMIT_V          12.0f     // [V]: Hard limit on output voltage, in volts. Effectively limits PWM duty cycle proportionally to power supply voltage.
#define MOTOR_VOLTAGE_LIMIT_V           12.0f     // [V]: Global voltage limit. Limits Q-axis voltage.
#define MOTOR_CURRENT_LIMIT_A           4.0f      // [A]: Global current limit. Limits Q-axis current.
/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/
typedef enum {
  STATE_INIT = 0,
  STATE_RAMP,
  STATE_LOCK,
  STATE_CLOSED
} process_state_t;

static BLDCMotor *motor_p;
static Commander *commander_p;

static process_state_t state = STATE_INIT;
static float target_velocity = 0.0f;
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

  Serial.println("Sensorless example");

  static BLDCMotor motor(MOTOR_PP, MOTOR_RESISTANCE, MOTOR_KV, MOTOR_INDUCTANCE);
  static BLDCDriver6PWM driver(PWM_1H, PWM_1L, PWM_2H, PWM_2L, PWM_3H, PWM_3L, PWM_EN);
  static LowsideCurrentSense current_sense(0.007f, 10.0f, CURR_SEN_A, CURR_SEN_B, CURR_SEN_C);
  static MXLEMMINGObserverSensor observer(motor);
  static Commander commander(Serial);

  motor_p = &motor;
  commander_p = &commander;

  // Link observer as the "sensor"
  motor.linkSensor(&observer);

  // Driver setup
  driver.voltage_power_supply = DRIVER_PSU_VOLTAGE_V;
  driver.voltage_limit = DRIVER_VOLTAGE_LIMIT_V;
  driver.pwm_frequency = DRIVER_PWM_FREQ_HZ;
  driver.dead_zone = DRIVER_DEAD_ZONE;

  driver.init();
  driver.enable();

  motor.linkDriver(&driver);

  // Motor setup
  motor.foc_modulation = FOCModulationType::SpaceVectorPWM;
  motor.controller = MotionControlType::velocity_openloop;
  motor.torque_controller = TorqueControlType::voltage;

  // Velocity control
  motor.PID_velocity.P = 0.2f;
  motor.PID_velocity.I = 2.0f;
  motor.PID_velocity.D = 0.0f;
  motor.LPF_velocity.Tf = 0.01f;

  motor.current_limit = MOTOR_CURRENT_LIMIT_A;

#if ENABLE_MONITOR
  motor.useMonitoring(Serial);
  motor.monitor_variables = _MON_TARGET | _MON_CURR_Q | _MON_CURR_D | _MON_VEL;
#endif

  if (!motor.init()) {
    Serial.println("Motor init failed!");
    return;
  }

  current_sense.linkDriver(&driver);
  current_sense.init();
  motor.linkCurrentSense(&current_sense);

  // Sensorless: skip sensor alignment
  motor.sensor_direction = Direction::CW;
  motor.zero_electric_angle = 0.0f;
  if (!motor.initFOC()) {
    Serial.println("FOC init failed!");
    return;
  }

  commander.add('M', doMotor, "motor");

  Serial.println("Sensorless velocity control ready.");
  Serial.println("INIT");

  vTaskDelay(1000 / portTICK_PERIOD_MS);

  uint32_t t0 = millis();
  uint32_t now = t0;
  uint32_t lock_start = 0;
  float ramp_velocity = 0.0f;
  float dt = 0;


  while (1) {
    motor.loopFOC();

    now = millis();
    dt = 0.001f * (float)(now - t0);

    switch (state) {
      case STATE_INIT:
      {
        ramp_velocity = 0.0f;
        motor.move(ramp_velocity);
        state = STATE_RAMP;
        Serial.println("RAMP");
        break;
      }

      case STATE_RAMP:
      {
        ramp_velocity += RAMP_ACCELERATION * dt;
        if (ramp_velocity > OBSERVER_MIN_VELOCITY_TO_LOCK) {
          ramp_velocity = OBSERVER_MIN_VELOCITY_TO_LOCK;
        }
        motor.move(ramp_velocity);

        if (ramp_velocity >= OBSERVER_MIN_VELOCITY_TO_LOCK * 0.98f) {
          state = STATE_LOCK;
          lock_start = millis();
          Serial.println("LOCK");
        }
        break;
      }

      case STATE_LOCK:
      {
        motor.move(ramp_velocity);

        if (millis() - lock_start > LOCKING_DURATION_MS) {
          target_velocity = ramp_velocity;
          motor.target = ramp_velocity;
          motor.controller = MotionControlType::velocity;
          state = STATE_CLOSED;
          Serial.println("CLOSED");
        }
        break;
      }

      case STATE_CLOSED:
      {
        motor.move();
        break;
      }

    }

#if ENABLE_MONITOR
    motor.monitor();
#endif

    commander.run();

    vTaskDelay(xDelay);
  }
}

#endif // APPLICATION_EXAMPLE == EXAMPLE_SENSORLESS_VELOCITY_6PWM
