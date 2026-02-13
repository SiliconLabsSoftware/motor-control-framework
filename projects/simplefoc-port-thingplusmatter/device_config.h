/***************************************************************************//**
 * @file config.h
 * @brief Configuration header
 *******************************************************************************
 * # License
 * <b>Copyright 2025 Silicon Laboratories Inc. www.silabs.com</b>
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
#ifndef DEVICE_CONFIG_H
#define DEVICE_CONFIG_H

#define ENABLE_MONITOR              0         // [0/1]: Enable motor monitoring
#define MOTOR_PP                    8         // BLDC motor pole pairs
#define MOTOR_RESISTANCE            0.4       // [Ohm]: BLDC motor resistance
#define MOTOR_KV                    285       // [RPM/V]: Motor KV rate
#define MOTOR_INDUCTANCE            0.000165  // [H]: Motor phase inductance
#define DRIVER_SHUNT_RESISTANCE     0.007     // [Ohm]: Driver shunt resistance
#define DRIVER_SHUNT_GAIN           10.0      // [V/A]: Driver shunt gain

// Pin definitions for Sparkfun Thing Plus Matter
#define PWM_1H        D4
#define PWM_1L        D5
#define PWM_2H        D6
#define PWM_2L        D7
#define PWM_3H        D8
#define PWM_3L        D9
#define PWM_EN        D10
#define HALL_A        D3
#define HALL_B        D0
#define HALL_C        D11
#define CURR_SEN_A    A5
#define CURR_SEN_B    A4
#define CURR_SEN_C    A3

#define EXAMPLE_CUSTOM                    0
#define EXAMPLE_OPEN_LOOP_VELOCITY_6PWM   1
#define EXAMPLE_HALL_SENSOR_VELOCITY_6PWM 2
#define EXAMPLE_TORQUE_VELOCITY_6PWM      3

#define APPLICATION_EXAMPLE  EXAMPLE_CUSTOM
// Add more device configurations as needed

#endif // DEVICE_CONFIG_H
