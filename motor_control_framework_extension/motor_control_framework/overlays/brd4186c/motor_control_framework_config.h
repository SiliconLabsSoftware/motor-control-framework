/***************************************************************************//**
 * @file motor_control_framework_config.h
 * @brief Motor Control Framework configuration - BRD4186C overlay
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

#ifndef MOTOR_CONTROL_FRAMEWORK_CONFIG_H
#define MOTOR_CONTROL_FRAMEWORK_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Runtime options

// <q ENABLE_MONITOR> Enable motor monitoring
// <d> 0
#define ENABLE_MONITOR              0

// <q ENABLE_BLE> Enable BLE interface
// <d> 1
#define ENABLE_BLE                  1

// </h>

// <h> Motor electrical parameters

// <o MOTOR_PP> BLDC motor pole pairs <1-100>
// <d> 8
#define MOTOR_PP                    8

// <o MOTOR_RESISTANCE_mOhm> Phase resistance (mOhm)
// <d> 400
#define MOTOR_RESISTANCE_mOhm            400
#define MOTOR_RESISTANCE                (float)(MOTOR_RESISTANCE_mOhm / 1000.0f)

// <o MOTOR_KV> Motor KV rating (RPM per volt) <1-2000>
// <d> 285
#define MOTOR_KV                    285

// <o MOTOR_INDUCTANCE_uH> Phase inductance (µH)
// <d> 165
#define MOTOR_INDUCTANCE_uH            165
#define MOTOR_INDUCTANCE                (float)(MOTOR_INDUCTANCE_uH / 1000000.0f)

// </h>

// <h> Current sense front-end

// <o DRIVER_SHUNT_RESISTANCE_mOhm> Shunt resistance (mOhm)
// <d> 7
#define DRIVER_SHUNT_RESISTANCE_mOhm     7
#define DRIVER_SHUNT_RESISTANCE      (float)(DRIVER_SHUNT_RESISTANCE_mOhm / 1000.0f)

// <o DRIVER_SHUNT_GAIN_mV_A> Shunt amplifier gain (mV/A)
// <d> 10000
#define DRIVER_SHUNT_GAIN_mV_A           10000
#define DRIVER_SHUNT_GAIN            (float)(DRIVER_SHUNT_GAIN_mV_A / 1000.0)

// </h>

// <h> Pin map (BRD4186C wiring. Use 'NA' for not applicable.)

#define MC_PIN_UNSET    (-2)
#define NA              (-1)

// <s.16 PWM_1H> Phase 1 high-side PWM pin
// <d> "PB0"
#define PWM_1H        PB0

// <s.16 PWM_1L> Phase 1 low-side PWM pin
// <d> "PA8"
#define PWM_1L        PA8

// <s.16 PWM_2H> Phase 2 high-side PWM pin
// <d> "PA9"
#define PWM_2H        PA9

// <s.16 PWM_2L> Phase 2 low-side PWM pin
// <d> "PB5"
#define PWM_2L        PB5

// <s.16 PWM_3H> Phase 3 high-side PWM pin
// <d> "PA0"
#define PWM_3H        PA0

// <s.16 PWM_3L> Phase 3 low-side PWM pin
// <d> "PB2"
#define PWM_3L        PB2

// <s.16 PWM_EN> Driver enable pin
// <d> "PA4"
#define PWM_EN        PA4

// <s.16 HALL_A> Hall sensor A
// <d> "PB4"
#define HALL_A        PB4

// <s.16 HALL_B> Hall sensor B
// <d> "PB1"
#define HALL_B        PB1

// <s.16 HALL_C> Hall sensor C
// <d> "PB3"
#define HALL_C        PB3

// <s.16 CURR_SEN_A> Phase A current sense input
// <d> "PC9"
#define CURR_SEN_A    PC9

// <s.16 CURR_SEN_B> Phase B current sense input
// <d> "PD5"
#define CURR_SEN_B    PD5

// <s.16 CURR_SEN_C> Phase C current sense input
// <d> "PD4"
#define CURR_SEN_C    PD4

// <s.16 SPI_MOSI> SPI MOSI
// <d> "PC1"
#define SPI_MOSI      PC1

// <s.16 SPI_MISO> SPI MISO
// <d> "PC6"
#define SPI_MISO      PC6

// <s.16 SPI_SCK> SPI clock
// <d> "PC3"
#define SPI_SCK       PC3

// <s.16 SPI_CS> SPI chip select
// <d> "PC8"
#define SPI_CS        PC8

// </h>

#if (PWM_1H == MC_PIN_UNSET)      \
  || (PWM_1L == MC_PIN_UNSET)     \
  || (PWM_2H == MC_PIN_UNSET)     \
  || (PWM_2L == MC_PIN_UNSET)     \
  || (PWM_3H == MC_PIN_UNSET)     \
  || (PWM_3L == MC_PIN_UNSET)     \
  || (PWM_EN == MC_PIN_UNSET)     \
  || (HALL_A == MC_PIN_UNSET)     \
  || (HALL_B == MC_PIN_UNSET)     \
  || (HALL_C == MC_PIN_UNSET)     \
  || (CURR_SEN_A == MC_PIN_UNSET) \
  || (CURR_SEN_B == MC_PIN_UNSET) \
  || (CURR_SEN_C == MC_PIN_UNSET) \
  || (SPI_MOSI == MC_PIN_UNSET)   \
  || (SPI_MISO == MC_PIN_UNSET)   \
  || (SPI_SCK == MC_PIN_UNSET)    \
  || (SPI_CS == MC_PIN_UNSET)
#error Motor Control Framework: configure all pins in Project Configurator (Pin map section).
#endif

// <<< end of configuration section >>>

#endif // MOTOR_CONTROL_FRAMEWORK_CONFIG_H
