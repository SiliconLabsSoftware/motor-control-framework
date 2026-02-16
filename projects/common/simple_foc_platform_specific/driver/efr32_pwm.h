/***************************************************************************//**
 * @file efr32_pwm.h
 * @brief EFR32 PWM driver definitions
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
#ifndef EFR32_DRIVER_PWM_MCU_H
#define EFR32_DRIVER_PWM_MCU_H

#include "sl_hal_timer.h"

#ifndef SILABBS_DEFAULT_DEAD_TIME
#define SILABBS_DEFAULT_DEAD_TIME 3
#endif

typedef void (*prevTimerInitCCFn)(sl_hal_timer_channel_init_t*, void *params);
typedef void (*prevTimerInitFn)(sl_hal_timer_init_t*, void *params);

typedef enum {
  PWM_P_ACTIVE_HIGH = 0,
  PWM_P_ACTIVE_LOW = 1
} EFR32PwmPolarity;

typedef struct {
  int frequency;              /**< PWM frequency */
  bool outInvert;             /**< Invert output */
  EFR32PwmPolarity polarity;  /**< PWM polarity */
} EFR32PwmConfig;

typedef struct {
  uint32_t deadTimeNs;
  uint32_t outputMask;
} EFR32PwmDeadTimeConfig;

typedef struct {
  TIMER_TypeDef *timer;       /**< TIMER instance */
  uint8_t channel;            /**< TIMER channel */
  uint8_t port;               /**< GPIO port */
  uint8_t pin;                /**< GPIO pin */
} EFR32PwmHiInstance;

typedef struct {
  uint8_t port;
  uint8_t pin;
} EFR32PwmLoInstance;

typedef struct {
  EFR32PwmHiInstance h;
  EFR32PwmLoInstance l;
} EFR32PwmInstance;

// High Side
void pwmHiConfig(
  EFR32PwmInstance *inst,
  TIMER_TypeDef *timer,
  const int pin,
  const uint8_t channel);

void pwmHiInit(
  EFR32PwmInstance *inst,
  EFR32PwmConfig *config,
  prevTimerInitCCFn fn,
  void *params);

void pwmHiDeinit(
  EFR32PwmInstance *inst);

void pwmHiOn(
  EFR32PwmInstance *inst);

void pwmHiOff(
  EFR32PwmInstance *inst);

void pwmHiSetDutyCycle(
  EFR32PwmInstance *inst,
  float percent);

float pwmHiGetDutyCycle(
  EFR32PwmInstance *inst);

// Low Side
void pwmLoConfig(
  EFR32PwmInstance *inst,
  const int pin);

void pwmLoInit(
  EFR32PwmInstance *inst);

void pwmLoDeinit(
  EFR32PwmInstance *inst);

void pwmLoOn(
  EFR32PwmInstance *inst);

void pwmLoOff(
  EFR32PwmInstance *inst);

// Pwm
void pwmInit(
  EFR32PwmInstance *inst,
  EFR32PwmConfig *cfg,
  prevTimerInitCCFn fn,
  void *params);

void pwmDeinit(
  EFR32PwmInstance *inst);

void pwmOn(
  EFR32PwmInstance *inst);

void pwmOff(
  EFR32PwmInstance *inst);

void pwmStart(
  EFR32PwmInstance *inst,
  prevTimerInitFn fn,
  void *params);

void pwmDeadTimeInit(
  EFR32PwmInstance *inst,
  EFR32PwmDeadTimeConfig *config);

#endif
