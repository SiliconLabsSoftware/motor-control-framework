/***************************************************************************//**
 * @file motor_control_framework_config.h
 * @brief Motor Control Framework configuration (Configuration Wizard)
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
 // <i> [0/1]: When set, application code may emit extra status / telemetry.
 // <d> 0
 #define ENABLE_MONITOR              0
 
 // <q ENABLE_BLE> Enable BLE interface
 // <i> [0/1]: When set, BLE stack and application BLE paths are compiled in.
 // <d> 1
 #define ENABLE_BLE                  1
 
 // </h>
 
 // <h> Motor electrical parameters
 
 // <o MOTOR_PP> BLDC motor pole pairs <1-100>
 // <d> 8
 #define MOTOR_PP                    8
 
// <o MOTOR_RESISTANCE_mOhm> Phase resistance (mOhm)
// <i> [mOhm]: BLDC motor phase resistance.
// <d> 400
#define MOTOR_RESISTANCE_mOhm            400

#define MOTOR_RESISTANCE                (float)(MOTOR_RESISTANCE_mOhm / 1000.0f)
 
 // <o MOTOR_KV> Motor KV rating (RPM per volt) <1-2000>
 // <i> [RPM/V]: Manufacturer KV rating.
 // <d> 285
 #define MOTOR_KV                    285
 
 // <o MOTOR_INDUCTANCE_uH> Phase inductance (µH)
 // <i> [H]: Motor phase inductance.
 // <d> 165
 #define MOTOR_INDUCTANCE_uH            165

 #define MOTOR_INDUCTANCE                (float)(MOTOR_INDUCTANCE_uH / 1000000.0f)
 
 // </h>
 
 // <h> Current sense front-end
 
 // <o DRIVER_SHUNT_RESISTANCE_mOhm> Shunt resistance (mOhm)
 // <i> [mOhm]: Sense resistor value at the driver.
 // <d> 7
 #define DRIVER_SHUNT_RESISTANCE_mOhm     7

 #define DRIVER_SHUNT_RESISTANCE      (float)(DRIVER_SHUNT_RESISTANCE_mOhm / 1000.0f)
 
 // <o DRIVER_SHUNT_GAIN_mV_A> Shunt amplifier gain (mV/A)
 // <i> [mV/A]: Amplifier gain from phase current to sense voltage.
 // <d> 10000
#define DRIVER_SHUNT_GAIN_mV_A           10000

#define DRIVER_SHUNT_GAIN            (float)(DRIVER_SHUNT_GAIN_mV_A / 1000.0)
 
// </h>

// <h> Pin map (Enter port pin names (e.g. 'PB0'). Build fails until all are set. Use 'NA' for not applicable.) 

#define MC_PIN_UNSET    (-2)
#define NA              (-1)

// <s.16 PWM_1H> Phase 1 high-side PWM pin
// <d> "MC_PIN_UNSET"
#define PWM_1H        MC_PIN_UNSET

// <s.16 PWM_1L> Phase 1 low-side PWM pin
// <d> "MC_PIN_UNSET"
#define PWM_1L        MC_PIN_UNSET

// <s.16 PWM_2H> Phase 2 high-side PWM pin
// <d> "MC_PIN_UNSET"
#define PWM_2H        MC_PIN_UNSET

// <s.16 PWM_2L> Phase 2 low-side PWM pin
// <d> "MC_PIN_UNSET"
#define PWM_2L        MC_PIN_UNSET

// <s.16 PWM_3H> Phase 3 high-side PWM pin
// <d> "MC_PIN_UNSET"
#define PWM_3H        MC_PIN_UNSET

// <s.16 PWM_3L> Phase 3 low-side PWM pin
// <d> "MC_PIN_UNSET"
#define PWM_3L        MC_PIN_UNSET

// <s.16 PWM_EN> Driver enable pin
// <d> "MC_PIN_UNSET"
#define PWM_EN        MC_PIN_UNSET

// <s.16 HALL_A> Hall sensor A
// <d> "MC_PIN_UNSET"
#define HALL_A        MC_PIN_UNSET

// <s.16 HALL_B> Hall sensor B
// <d> "MC_PIN_UNSET"
#define HALL_B        MC_PIN_UNSET

// <s.16 HALL_C> Hall sensor C
// <d> "MC_PIN_UNSET"
#define HALL_C        MC_PIN_UNSET

// <s.16 CURR_SEN_A> Phase A current sense input
// <d> "MC_PIN_UNSET"
#define CURR_SEN_A    MC_PIN_UNSET

// <s.16 CURR_SEN_B> Phase B current sense input
// <d> "MC_PIN_UNSET"
#define CURR_SEN_B    MC_PIN_UNSET

// <s.16 CURR_SEN_C> Phase C current sense input
// <d> "MC_PIN_UNSET"
#define CURR_SEN_C    MC_PIN_UNSET

// <s.16 SPI_MOSI> SPI MOSI
// <d> "MC_PIN_UNSET"
#define SPI_MOSI      MC_PIN_UNSET

// <s.16 SPI_MISO> SPI MISO
// <d> "MC_PIN_UNSET"
#define SPI_MISO      MC_PIN_UNSET

// <s.16 SPI_SCK> SPI clock
// <d> "MC_PIN_UNSET"
#define SPI_SCK       MC_PIN_UNSET

// <s.16 SPI_CS> SPI chip select
// <d> "MC_PIN_UNSET"
#define SPI_CS        MC_PIN_UNSET

// </h>

#if (PWM_1H == MC_PIN_UNSET) \
 || (PWM_1L == MC_PIN_UNSET) \
 || (PWM_2H == MC_PIN_UNSET) \
 || (PWM_2L == MC_PIN_UNSET) \
 || (PWM_3H == MC_PIN_UNSET) \
 || (PWM_3L == MC_PIN_UNSET) \
 || (PWM_EN == MC_PIN_UNSET) \
 || (HALL_A == MC_PIN_UNSET) \
 || (HALL_B == MC_PIN_UNSET) \
 || (HALL_C == MC_PIN_UNSET) \
 || (CURR_SEN_A == MC_PIN_UNSET) \
 || (CURR_SEN_B == MC_PIN_UNSET) \
 || (CURR_SEN_C == MC_PIN_UNSET) \
 || (SPI_MOSI == MC_PIN_UNSET) \
 || (SPI_MISO == MC_PIN_UNSET) \
 || (SPI_SCK == MC_PIN_UNSET) \
 || (SPI_CS == MC_PIN_UNSET)
#error Motor Control Framework: configure all pins in Project Configurator (Pin map section).
#endif

// <<< end of configuration section >>>

#endif // MOTOR_CONTROL_FRAMEWORK_CONFIG_H
