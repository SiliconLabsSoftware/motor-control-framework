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

#define ENABLE_MONITOR  0
#define MOTOR_PP        8  // BLDC motor pole pairs

// Pin definitions for BRD4186C
#define PWM_1H        PB0
#define PWM_1L        PA8
#define PWM_2H        PA9
#define PWM_2L        PB5
#define PWM_3H        PA0
#define PWM_3L        PB2
#define PWM_EN        PA4
#define HALL_A        PB4
#define HALL_B        PB1
#define HALL_C        PB3
#define CURR_SEN_A    PC9
#define CURR_SEN_B    PD5
#define CURR_SEN_C    PD4
#define SPI_MOSI      PC1
#define SPI_MISO      PC6
#define SPI_SCK       PC3
#define SPI_CS        PC8

#define EXAMPLE_CUSTOM                    0
#define EXAMPLE_OPEN_LOOP_VELOCITY_6PWM   1
#define EXAMPLE_HALL_SENSOR_VELOCITY_6PWM 2
#define EXAMPLE_TORQUE_VELOCITY_6PWM      3

#define APPLICATION_EXAMPLE  EXAMPLE_CUSTOM
// Add more device configurations as needed

#endif // DEVICE_CONFIG_H
