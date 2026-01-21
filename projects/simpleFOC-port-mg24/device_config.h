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

#include "em_device.h"

#define ENABLE_MONITOR  0
#define MOTOR_PP        8  // BLDC motor pole pairs

// pinout config
#if defined(MGM240PB32VNA)
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
#define CURR_SEN_B    A3
#define CURR_SEN_C    A4
#endif // MGM240PB32VNA

#define EXAMPLE_CUSTOM                    0
#define EXAMPLE_OPEN_LOOP_VELOCITY_6PWM   1
#define EXAMPLE_HALL_SENSOR_VELOCITY_6PWM 2
#define EXAMPLE_TORQUE_VELOCITY_6PWM      3

#define APPLICATION_EXAMPLE  3
// Add more device configurations as needed

#endif // DEVICE_CONFIG_H