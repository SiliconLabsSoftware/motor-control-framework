/***************************************************************************//**
 * @file efr32_mcu.cpp
 * @brief EFR32 MCU specific driver functions
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
#include "sl_clock_manager.h"
#include "sl_hal_prs.h"
#include "efr32_pwm.h"
#include "efr32_mcu.h"

static EFR32DriverParams driver_params[SILABS_DEFAULT_MAX_MOTOR_COUNT];
static uint8_t driver_params_index = 0;

void _getPrsUnderflowSignal(TIMER_TypeDef *timer, uint32_t *signal)
{
  if (!timer || !signal) {
    return;
  }

  switch ((uint32_t) timer) {
    case TIMER0_BASE:
      *signal = SL_HAL_PRS_ASYNC_TIMER0_UF;
      break;

    case TIMER1_BASE:
      *signal = SL_HAL_PRS_ASYNC_TIMER1_UF;
      break;

    case TIMER2_BASE:
      *signal = SL_HAL_PRS_ASYNC_TIMER2_UF;
      break;

    default:
      break;
  }
}

void _getPrsConsumerEvent(TIMER_TypeDef *timer, uint8_t channel, uint32_t *event)
{
  if (!timer || !event) {
    return;
  }

  *event = SL_HAL_PRS_CONSUMER_NONE;
  switch ((uint32_t) timer) {
    case TIMER0_BASE:
      *event = (channel == 0) ? SL_HAL_PRS_CONSUMER_TIMER0_CC0
               : (channel == 1) ? SL_HAL_PRS_CONSUMER_TIMER0_CC1
               : (channel == 2) ? SL_HAL_PRS_CONSUMER_TIMER0_CC2
               : SL_HAL_PRS_CONSUMER_NONE;
      break;
    case TIMER1_BASE:
      *event = (channel == 0) ? SL_HAL_PRS_CONSUMER_TIMER1_CC0
               : (channel == 1) ? SL_HAL_PRS_CONSUMER_TIMER1_CC1
               : (channel == 2) ? SL_HAL_PRS_CONSUMER_TIMER1_CC2
               : SL_HAL_PRS_CONSUMER_NONE;
      break;
    case TIMER2_BASE:
      *event = (channel == 0) ? SL_HAL_PRS_CONSUMER_TIMER2_CC0
               : (channel == 1) ? SL_HAL_PRS_CONSUMER_TIMER2_CC1
               : (channel == 2) ? SL_HAL_PRS_CONSUMER_TIMER2_CC2
               : SL_HAL_PRS_CONSUMER_NONE;
      break;
    default:
      break;
  }
}

// Callbacks
static void _alignPWMTimers(
  sl_hal_timer_channel_init_t *initCC,
  void *params
  )
{
  EFR32PwmInstance *p = (EFR32PwmInstance*)params;
  if (!p || !initCC) {
    return;
  }

  sl_clock_manager_enable_bus_clock(SL_BUS_CLOCK_PRS);

  uint32_t prsSignal = 0;
  uint32_t prsEvent = SL_HAL_PRS_CONSUMER_NONE;

  initCC->input_type = SL_HAL_TIMER_CHANNEL_INPUT_PRS_ASYNC_PULSE;

  _getPrsUnderflowSignal(p->h.timer, &prsSignal);
  _getPrsConsumerEvent(p->h.timer, p->h.channel, &prsEvent);

  if (!prsSignal || (prsEvent == SL_HAL_PRS_CONSUMER_NONE)) {
    return;
  }

  sl_hal_prs_async_connect_channel_producer(SILABS_PWM_PRS_CHANNEL, (sl_hal_prs_async_producer_signal_t)prsSignal);
  sl_hal_prs_connect_channel_consumer(SILABS_PWM_PRS_CHANNEL, SL_HAL_PRS_TYPE_ASYNC, (sl_hal_prs_consumer_event_t)prsEvent);
}

static void _configPWMMode(
  sl_hal_timer_init_t *init,
  void *params
  )
{
  if (!init) {
    return;
  }
  _UNUSED(params);
  init->count_mode = SL_HAL_TIMER_MODE_UPDOWN;
}

static void _alignPWMStart(
  sl_hal_timer_init_t *init,
  void *params
  )
{
  if (!init) {
    return;
  }
  _UNUSED(params);
  init->count_mode = SL_HAL_TIMER_MODE_UPDOWN;
  init->input_rise_action = SL_HAL_TIMER_INPUT_ACTION_RELOAD_START;
}

static void _setSinglePhaseState(EFR32PwmInstance *inst, PhaseState state)
{
  if (!inst) {
    return;
  }

  switch (state) {
    case PhaseState::PHASE_OFF:
      pwmOff(inst);
      break;

    default:
      pwmOn(inst);
      break;
  }
}

void *_configure1PWM(long pwm_frequency, const int pinA)
{
  if (driver_params_index >= SILABS_DEFAULT_MAX_MOTOR_COUNT) {
    return SIMPLEFOC_DRIVER_INIT_FAILED;
  }

  EFR32DriverParams *params = &driver_params[driver_params_index++];
  if (!params) {
    return SIMPLEFOC_DRIVER_INIT_FAILED;
  }

  if (!pwm_frequency || !_isset(pwm_frequency)) {
    pwm_frequency = SILABS_DEFAULT_PWM_FREQUENCY;
  } else {
    pwm_frequency = _constrain(pwm_frequency, 0, SILABS_DEFAULT_PWM_FREQUENCY);
  }

  params->pwm_frequency = pwm_frequency;
  params->noPwmChannel = 1;

  // Ensure all PWMs use the same TIMER instance
  pwmHiConfig(&params->inst[0], SILABS_DEFAULT_PWM_PERPHERAL, pinA, 0);

  // Initialize PWM
  EFR32PwmConfig pwmConfig;
  pwmConfig.frequency = pwm_frequency;
  pwmConfig.polarity = PWM_P_ACTIVE_LOW;
  pwmConfig.outInvert = true;

  pwmHiInit(&params->inst[0], &pwmConfig, NULL, NULL);

  // PWM On
  pwmHiOn(&params->inst[0]);

  // Start PWM
  pwmStart(&params->inst[0], _configPWMMode, NULL);

  return params;
}

void* _configure2PWM(long pwm_frequency, const int pinA, const int pinB)
{
  if (driver_params_index >= SILABS_DEFAULT_MAX_MOTOR_COUNT) {
    return SIMPLEFOC_DRIVER_INIT_FAILED;
  }

  EFR32DriverParams *params = &driver_params[driver_params_index++];
  if (!params) {
    return SIMPLEFOC_DRIVER_INIT_FAILED;
  }

  if (!pwm_frequency || !_isset(pwm_frequency)) {
    pwm_frequency = SILABS_DEFAULT_PWM_FREQUENCY;
  } else {
    pwm_frequency = _constrain(pwm_frequency, 0, SILABS_DEFAULT_PWM_FREQUENCY);
  }

  params->pwm_frequency = pwm_frequency;
  params->noPwmChannel = 2;

  // Ensure all PWMs use the same TIMER instance
  pwmHiConfig(&params->inst[0], SILABS_DEFAULT_PWM_PERPHERAL, pinA, 0);
  pwmHiConfig(&params->inst[1], SILABS_DEFAULT_PWM_PERPHERAL, pinB, 1);

  // Initialize PWM
  EFR32PwmConfig pwmConfig;
  pwmConfig.frequency = pwm_frequency << 1;
  pwmConfig.polarity = PWM_P_ACTIVE_LOW;
  pwmConfig.outInvert = true;

  pwmHiInit(&params->inst[0], &pwmConfig, NULL, NULL);
  pwmHiInit(&params->inst[1], &pwmConfig, NULL, NULL);

  // PWM On
  pwmHiOn(&params->inst[0]);
  pwmHiOn(&params->inst[1]);

  // Start PWM
  pwmStart(&params->inst[0], _configPWMMode, NULL);

  return params;
}

void* _configure3PWM(
  long pwm_frequency,
  const int pinA,
  const int pinB,
  const int pinC
  )
{
  if (driver_params_index >= SILABS_DEFAULT_MAX_MOTOR_COUNT) {
    return SIMPLEFOC_DRIVER_INIT_FAILED;
  }

  EFR32DriverParams *params = &driver_params[driver_params_index++];
  if (!params) {
    return SIMPLEFOC_DRIVER_INIT_FAILED;
  }

  if (!pwm_frequency || !_isset(pwm_frequency)) {
    pwm_frequency = SILABS_DEFAULT_PWM_FREQUENCY;
  } else {
    pwm_frequency = _constrain(pwm_frequency, 0, SILABS_DEFAULT_PWM_FREQUENCY);
  }

  params->pwm_frequency = pwm_frequency;
  params->noPwmChannel = 3;

  // Ensure all PWMs use the same TIMER instance
  pwmHiConfig(&params->inst[0], SILABS_DEFAULT_PWM_PERPHERAL, pinA, 0);
  pwmHiConfig(&params->inst[1], SILABS_DEFAULT_PWM_PERPHERAL, pinB, 1);
  pwmHiConfig(&params->inst[2], SILABS_DEFAULT_PWM_PERPHERAL, pinC, 2);

  // Initialize PWM
  EFR32PwmConfig pwmConfig;
  pwmConfig.frequency = pwm_frequency << 1;
  pwmConfig.polarity = PWM_P_ACTIVE_LOW;
  pwmConfig.outInvert = true;

  pwmHiInit(&params->inst[0], &pwmConfig, NULL, NULL);
  pwmHiInit(&params->inst[1], &pwmConfig, NULL, NULL);
  pwmHiInit(&params->inst[2], &pwmConfig, NULL, NULL);

  // PWM On
  pwmHiOn(&params->inst[0]);
  pwmHiOn(&params->inst[1]);
  pwmHiOn(&params->inst[2]);

  // Start PWM
  pwmStart(&params->inst[0], _configPWMMode, NULL);

  return params;
}

void* _configure4PWM(
  long pwm_frequency,
  const int pin1A,
  const int pin1B,
  const int pin2A,
  const int pin2B
  )
{
  if (driver_params_index >= SILABS_DEFAULT_MAX_MOTOR_COUNT) {
    return SIMPLEFOC_DRIVER_INIT_FAILED;
  }

  EFR32DriverParams *params = &driver_params[driver_params_index++];
  if (!params) {
    return SIMPLEFOC_DRIVER_INIT_FAILED;
  }

  if (!pwm_frequency || !_isset(pwm_frequency)) {
    pwm_frequency = SILABS_DEFAULT_PWM_FREQUENCY;
  } else {
    pwm_frequency = _constrain(pwm_frequency, 0, SILABS_DEFAULT_PWM_FREQUENCY);
  }

  params->pwm_frequency = pwm_frequency;
  params->noPwmChannel = 4;

  // Ensure all PWMs use the same TIMER instance
  pwmHiConfig(&params->inst[0], SILABS_DEFAULT_PWM_PERPHERAL, pin1A, 0);
  pwmHiConfig(&params->inst[1], SILABS_DEFAULT_PWM_PERPHERAL, pin1B, 1);
  pwmHiConfig(&params->inst[2], SILABS_DEFAULT_PWM_PERPHERAL, pin2A, 2);
  pwmHiConfig(&params->inst[3], SILABS_SECOND_PWM_PERPHERAL, pin2B, 0);

  // Initialize PWM
  EFR32PwmConfig pwmConfig;
  pwmConfig.frequency = pwm_frequency << 1;
  pwmConfig.polarity = PWM_P_ACTIVE_LOW;
  pwmConfig.outInvert = true;

  pwmHiInit(&params->inst[0], &pwmConfig, NULL, NULL);
  pwmHiInit(&params->inst[1], &pwmConfig, NULL, NULL);
  pwmHiInit(&params->inst[2], &pwmConfig, NULL, NULL);
  pwmHiInit(&params->inst[3], &pwmConfig, _alignPWMTimers, &params->inst[0]);

  // PWM On
  pwmHiOn(&params->inst[0]);
  pwmHiOn(&params->inst[1]);
  pwmHiOn(&params->inst[2]);
  pwmHiOn(&params->inst[3]);

  // Start PWM
  pwmStart(&params->inst[0], _configPWMMode, NULL);
  pwmStart(&params->inst[3], _alignPWMStart, NULL);

  return params;
}

void* _configure6PWM(
  long pwm_frequency,
  float dead_zone,
  const int pinA_h,
  const int pinA_l,
  const int pinB_h,
  const int pinB_l,
  const int pinC_h,
  const int pinC_l
  )
{
  if (driver_params_index >= SILABS_DEFAULT_MAX_MOTOR_COUNT) {
    return SIMPLEFOC_DRIVER_INIT_FAILED;
  }

  EFR32DriverParams *params = &driver_params[driver_params_index++];
  if (!params) {
    return SIMPLEFOC_DRIVER_INIT_FAILED;
  }

  if (!pwm_frequency || !_isset(pwm_frequency)) {
    pwm_frequency = SILABS_DEFAULT_PWM_FREQUENCY;
  } else {
    pwm_frequency = _constrain(pwm_frequency, 0, SILABS_DEFAULT_PWM_FREQUENCY);
  }

  params->pwm_frequency = pwm_frequency;
  params->dead_zone = (dead_zone == NOT_SET) ? SILABS_DEFAULT_DEAD_ZONE : dead_zone;
  params->lowside = true;
  params->noPwmChannel = 3;

  // Ensure all PWMs use the same TIMER instance
  pwmHiConfig(&params->inst[0], SILABS_DEFAULT_PWM_PERPHERAL, pinA_h, 0);
  pwmLoConfig(&params->inst[0], pinA_l);

  pwmHiConfig(&params->inst[1], SILABS_DEFAULT_PWM_PERPHERAL, pinB_h, 1);
  pwmLoConfig(&params->inst[1], pinB_l);

  pwmHiConfig(&params->inst[2], SILABS_DEFAULT_PWM_PERPHERAL, pinC_h, 2);
  pwmLoConfig(&params->inst[2], pinC_l);

  // Initialize PWM
  EFR32PwmConfig pwmConfig;
  pwmConfig.frequency = pwm_frequency << 1;
  pwmConfig.polarity = PWM_P_ACTIVE_LOW;
  pwmConfig.outInvert = true;

  pwmInit(&params->inst[0], &pwmConfig, NULL, NULL);
  pwmInit(&params->inst[1], &pwmConfig, NULL, NULL);
  pwmInit(&params->inst[2], &pwmConfig, NULL, NULL);

  // Dead Time PWM
  uint32_t deadTimeNs = (uint32_t)((1e9f / pwm_frequency) * params->dead_zone);
  EFR32PwmDeadTimeConfig deadTimeConfig;
  deadTimeConfig.deadTimeNs = deadTimeNs >> 1;
  deadTimeConfig.outputMask = TIMER_DTOGEN_DTOGCC0EN
                              | TIMER_DTOGEN_DTOGCC1EN
                              | TIMER_DTOGEN_DTOGCC2EN
                              | TIMER_DTOGEN_DTOGCDTI0EN
                              | TIMER_DTOGEN_DTOGCDTI1EN
                              | TIMER_DTOGEN_DTOGCDTI2EN;
  pwmDeadTimeInit(&params->inst[0], &deadTimeConfig);

  // PWM On
  pwmOn(&params->inst[0]);
  pwmOn(&params->inst[1]);
  pwmOn(&params->inst[2]);

  // Start PWM
  pwmStart(&params->inst[0], _configPWMMode, NULL);

  return params;
}

void _writeDutyCycle1PWM(float dc_a, void* params)
{
  EFR32DriverParams *p = (EFR32DriverParams*) params;
  if (!p) {
    return;
  }

  pwmHiSetDutyCycle(&p->inst[0], dc_a * 100.0f);
}

void _writeDutyCycle2PWM(float dc_a, float dc_b, void* params)
{
  EFR32DriverParams *p = (EFR32DriverParams*) params;
  if (!p) {
    return;
  }

  pwmHiSetDutyCycle(&p->inst[0], dc_a * 100.0f);
  pwmHiSetDutyCycle(&p->inst[1], dc_b * 100.0f);
}

void _writeDutyCycle3PWM(float dc_a, float dc_b, float dc_c, void* params)
{
  EFR32DriverParams *p = (EFR32DriverParams*) params;
  if (!p) {
    return;
  }

  pwmHiSetDutyCycle(&p->inst[0], dc_a * 100.0f);
  pwmHiSetDutyCycle(&p->inst[1], dc_b * 100.0f);
  pwmHiSetDutyCycle(&p->inst[2], dc_c * 100.0f);
}

void _writeDutyCycle4PWM(
  float dc_1a,
  float dc_1b,
  float dc_2a,
  float dc_2b,
  void* params
  )
{
  EFR32DriverParams *p = (EFR32DriverParams*) params;
  if (!p) {
    return;
  }

  pwmHiSetDutyCycle(&p->inst[0], dc_1a * 100.0f);
  pwmHiSetDutyCycle(&p->inst[1], dc_1b * 100.0f);
  pwmHiSetDutyCycle(&p->inst[2], dc_2a * 100.0f);
  pwmHiSetDutyCycle(&p->inst[3], dc_2b * 100.0f);
}

void _writeDutyCycle6PWM(
  float dc_a,
  float dc_b,
  float dc_c,
  PhaseState *phase_state,
  void* params
  )
{
  EFR32DriverParams *p = (EFR32DriverParams*) params;
  if (!p || !phase_state) {
    return;
  }

  _setSinglePhaseState(&p->inst[0], phase_state[0]);
  if (phase_state[0] == PhaseState::PHASE_OFF) {
    dc_a = 0.0f;
  }
  pwmHiSetDutyCycle(&p->inst[0], dc_a * 100);

  _setSinglePhaseState(&p->inst[1], phase_state[1]);
  if (phase_state[1] == PhaseState::PHASE_OFF) {
    dc_b = 0.0f;
  }
  pwmHiSetDutyCycle(&p->inst[1], dc_b * 100.0f);

  _setSinglePhaseState(&p->inst[2], phase_state[2]);
  if (phase_state[2] == PhaseState::PHASE_OFF) {
    dc_c = 0.0f;
  }
  pwmHiSetDutyCycle(&p->inst[2], dc_c * 100.0f);
}

void _startADC3PinConversionLowSide()
{
  // nothing to do
}
