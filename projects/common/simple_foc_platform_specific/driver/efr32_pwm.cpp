/***************************************************************************//**
 * @file efr32_pwm.cpp
 * @brief EFR32 PWM driver functions
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
#include <pinDefinitions.h>
#include "sl_clock_manager.h"
#include "sl_device_peripheral.h"
#include "sl_gpio.h"
#include "efr32_pwm.h"

static sl_peripheral_t _getTimerPeripheral(TIMER_TypeDef *timer)
{
#if defined(_CMU_HFCLKSEL_MASK) || defined(_CMU_CMD_HFCLKSEL_MASK)
  sl_peripheral_t timerPeripheral = NULL;
#elif defined(_CMU_SYSCLKCTRL_MASK)
  sl_peripheral_t timerPeripheral = NULL;
#else
#error "Unknown root of clock tree"
#endif

  switch ((uint32_t)timer) {
#if defined(TIMER0_BASE)
    case TIMER0_BASE:
      timerPeripheral = SL_PERIPHERAL_TIMER0;
      break;
#endif
#if defined(TIMER1_BASE)
    case TIMER1_BASE:
      timerPeripheral = SL_PERIPHERAL_TIMER1;
      break;
#endif
#if defined(TIMER2_BASE)
    case TIMER2_BASE:
      timerPeripheral = SL_PERIPHERAL_TIMER2;
      break;
#endif
#if defined(TIMER3_BASE)
    case TIMER3_BASE:
      timerPeripheral = SL_PERIPHERAL_TIMER3;
      break;
#endif
#if defined(TIMER4_BASE)
    case TIMER4_BASE:
      timerPeripheral = SL_PERIPHERAL_TIMER4;
      break;
#endif
#if defined(TIMER5_BASE)
    case TIMER5_BASE:
      timerPeripheral = SL_PERIPHERAL_TIMER5;
      break;
#endif
#if defined(TIMER6_BASE)
    case TIMER6_BASE:
      timerPeripheral = SL_PERIPHERAL_TIMER6;
      break;
#endif
#if defined(TIMER7_BASE)
    case TIMER7_BASE:
      timerPeripheral = SL_PERIPHERAL_TIMER7;
      break;
#endif
#if defined(TIMER8_BASE)
    case TIMER8_BASE:
      timerPeripheral = SL_PERIPHERAL_TIMER8;
      break;
#endif
#if defined(TIMER9_BASE)
    case TIMER9_BASE:
      timerPeripheral = SL_PERIPHERAL_TIMER9;
      break;
#endif
    default:
      break;
  }
  return timerPeripheral;
}

void pwmHiConfig(
  EFR32PwmInstance *inst,
  TIMER_TypeDef *timer,
  const int pin,
  const uint8_t channel
  )
{
  if (!inst) {
    return;
  }

  inst->h.timer = timer;
  inst->h.port = getSilabsPortFromArduinoPin(pinToPinName(pin));
  inst->h.pin = getSilabsPinFromArduinoPin(pinToPinName(pin));
  inst->h.channel = channel;
}

void pwmHiInit(
  EFR32PwmInstance *inst,
  EFR32PwmConfig *config,
  prevTimerInitCCFn fn,
  void *params
  )
{
  if (!inst || !config) {
    return;
  }

  // Enable Timer Clock
  sl_peripheral_t timerPeripheral = _getTimerPeripheral(inst->h.timer);

  if (NULL == timerPeripheral) {
    return;
  }
  sl_clock_manager_enable_bus_clock(timerPeripheral->bus_clock);

  // Initialize TIMER (configures mode/prescaler, leaves timer disabled)
  sl_hal_timer_init_t timerInit = SL_HAL_TIMER_INIT_DEFAULT;
  sl_hal_timer_init(inst->h.timer, &timerInit);

  // Set PWM pin as output
  sl_clock_manager_enable_bus_clock(SL_BUS_CLOCK_GPIO);
  sl_gpio_t gpio = {
    .port = inst->h.port,
    .pin = inst->h.pin
  };
  sl_gpio_set_pin_mode(&gpio, SL_GPIO_MODE_PUSH_PULL, config->polarity);

  // Set CC channel parameters
  sl_hal_timer_channel_init_t initCC = SL_HAL_TIMER_CHANNEL_INIT_DEFAULT;
  initCC.channel_mode = SL_HAL_TIMER_CHANNEL_MODE_PWM;
  if (config->outInvert) {
    initCC.output_invert = true;
  }
  if (fn) {
    fn(&initCC, params);
  }

  sl_hal_timer_channel_init(inst->h.timer, inst->h.channel, &initCC);

  volatile uint32_t *routeRegister = &GPIO->TIMERROUTE[TIMER_NUM(inst->h.timer)].CC0ROUTE;
  routeRegister += inst->h.channel;
  *routeRegister = (inst->h.port << _GPIO_TIMER_CC0ROUTE_PORT_SHIFT)
                   | (inst->h.pin << _GPIO_TIMER_CC0ROUTE_PIN_SHIFT);

  // sl_hal_timer_channel_init() leaves the timer disabled; enable again before register writes
  sl_hal_timer_enable(inst->h.timer);
  sl_hal_timer_wait_sync(inst->h.timer);

  // Configure TIMER frequency
  uint32_t timer_frequency = 0;
  sl_clock_manager_get_clock_branch_frequency(timerPeripheral->clk_branch, &timer_frequency);
  uint32_t top = (timer_frequency / (config->frequency)) - 1U;
  sl_hal_timer_set_top(inst->h.timer, top);

  // Set initial duty cycle to 0%
  sl_hal_timer_channel_set_compare(inst->h.timer, inst->h.channel, 0U);
}

void pwmHiDeinit(
  EFR32PwmInstance *inst
  )
{
  if (!inst) {
    return;
  }

  pwmHiOff(inst);

  volatile uint32_t *routeRegister = &GPIO->TIMERROUTE[TIMER_NUM(inst->h.timer)].CC0ROUTE;
  routeRegister += inst->h.channel;
  *routeRegister = 0;

  sl_hal_timer_reset(inst->h.timer);
  sl_gpio_t gpio = {
    .port = inst->h.port,
    .pin = inst->h.pin
  };
  sl_gpio_set_pin_mode(&gpio, SL_GPIO_MODE_DISABLED, false);

  sl_peripheral_t timerPeripheral = _getTimerPeripheral(inst->h.timer);
  if (NULL == timerPeripheral) {
    return;
  }
  sl_clock_manager_disable_bus_clock(timerPeripheral->bus_clock);
}

void pwmHiOn(
  EFR32PwmInstance *inst
  )
{
  if (!inst) {
    return;
  }
  GPIO->TIMERROUTE_SET[TIMER_NUM(inst->h.timer)].ROUTEEN = 1 << (inst->h.channel + _GPIO_TIMER_ROUTEEN_CC0PEN_SHIFT);
}

void pwmHiOff(
  EFR32PwmInstance *inst
  )
{
  if (!inst) {
    return;
  }
  GPIO->TIMERROUTE_CLR[TIMER_NUM(inst->h.timer)].ROUTEEN = 1 << (inst->h.channel + _GPIO_TIMER_ROUTEEN_CC0PEN_SHIFT);
}

void pwmHiSetDutyCycle(
  EFR32PwmInstance *inst,
  float percent
  )
{
  if (!inst || (percent > 100.0f)) {
    return;
  }

  // Ensure timer is enabled before writing compare buffer (HAL asserts otherwise)
  if ((inst->h.timer->EN & _TIMER_EN_EN_MASK) == 0) {
    sl_hal_timer_enable(inst->h.timer);
    sl_hal_timer_wait_sync(inst->h.timer);
  }

  uint32_t top = sl_hal_timer_get_top(inst->h.timer);
  volatile bool outInvert = inst->h.timer->CC[inst->h.channel].CTRL & TIMER_CC_CTRL_OUTINV;
  if (outInvert) {
    percent = 100 - percent;
  }
  sl_hal_timer_channel_set_compare_buffer(inst->h.timer, inst->h.channel, (uint32_t) (top * percent) / 100);
}

float pwmHiGetDutyCycle(
  EFR32PwmInstance *inst
  )
{
  if (!inst) {
    return 0;
  }
  uint32_t top = sl_hal_timer_get_top(inst->h.timer);
  uint32_t compare = sl_hal_timer_channel_get_capture(inst->h.timer, inst->h.channel);
  volatile bool outInvert = inst->h.timer->CC[inst->h.channel].CTRL & TIMER_CC_CTRL_OUTINV;
  float percent = (float)((compare * 100) / top);
  return outInvert ? (100 - percent) : percent;
}

void pwmLoConfig(
  EFR32PwmInstance *inst,
  const int pin
  )
{
  if (!inst) {
    return;
  }
  inst->l.port = getSilabsPortFromArduinoPin(pinToPinName(pin));
  inst->l.pin = getSilabsPinFromArduinoPin(pinToPinName(pin));
}

void pwmLoInit(
  EFR32PwmInstance *inst
  )
{
  if (!inst) {
    return;
  }

  // Low side PWM
  sl_clock_manager_enable_bus_clock(SL_BUS_CLOCK_GPIO);
  sl_gpio_t gpio = {
    .port = inst->l.port,
    .pin = inst->l.pin
  };
  sl_gpio_set_pin_mode(&gpio, SL_GPIO_MODE_PUSH_PULL, false);

  volatile uint32_t *routeRegister = &GPIO->TIMERROUTE[TIMER_NUM(inst->h.timer)].CDTI0ROUTE;
  routeRegister += inst->h.channel;
  *routeRegister = (inst->l.port << _GPIO_TIMER_CDTI0ROUTE_PORT_SHIFT)
                   | (inst->l.pin << _GPIO_TIMER_CDTI0ROUTE_PIN_SHIFT);
}

void pwmLoDeinit(
  EFR32PwmInstance *inst
  )
{
  if (!inst) {
    return;
  }

  pwmLoOff(inst);

  volatile uint32_t *routeRegister = &GPIO->TIMERROUTE[TIMER_NUM(inst->h.timer)].CDTI0ROUTE;
  routeRegister += inst->h.channel;
  *routeRegister = 0;

  sl_gpio_t gpio = {
    .port = inst->l.port,
    .pin = inst->l.pin
  };
  sl_gpio_set_pin_mode(&gpio, SL_GPIO_MODE_DISABLED, false);
}

void pwmLoOn(
  EFR32PwmInstance *inst
  )
{
  if (!inst) {
    return;
  }
  GPIO->TIMERROUTE_SET[TIMER_NUM(inst->h.timer)].ROUTEEN |= 1 << (inst->h.channel + _GPIO_TIMER_ROUTEEN_CCC0PEN_SHIFT);
}

void pwmLoOff(
  EFR32PwmInstance *inst
  )
{
  if (!inst) {
    return;
  }
  GPIO->TIMERROUTE_CLR[TIMER_NUM(inst->h.timer)].ROUTEEN |= 1 << (inst->h.channel + _GPIO_TIMER_ROUTEEN_CCC0PEN_SHIFT);
}

void pwmInit(
  EFR32PwmInstance *inst,
  EFR32PwmConfig *config,
  prevTimerInitCCFn fn,
  void *params
  )
{
  if (!inst || !config) {
    return;
  }
  pwmHiInit(inst, config, fn, params);
  pwmLoInit(inst);
}

void pwmDeinit(
  EFR32PwmInstance *inst
  )
{
  if (!inst) {
    return;
  }
  pwmHiDeinit(inst);
  pwmLoDeinit(inst);
}

void pwmOff(EFR32PwmInstance *inst)
{
  if (!inst) {
    return;
  }
  pwmHiOff(inst);
  pwmLoOff(inst);
}

void pwmOn(EFR32PwmInstance *inst)
{
  if (!inst) {
    return;
  }
  pwmHiOn(inst);
  pwmLoOn(inst);
}

void pwmStart(EFR32PwmInstance *inst, prevTimerInitFn fn, void *params)
{
  if (!inst) {
    return;
  }

  sl_hal_timer_init_t timerInit = SL_HAL_TIMER_INIT_DEFAULT;
  if (fn) {
    fn(&timerInit, params);
  }
  sl_hal_timer_init(inst->h.timer, &timerInit);

  sl_hal_timer_enable(inst->h.timer);
  sl_hal_timer_wait_sync(inst->h.timer);
  sl_hal_timer_start(inst->h.timer);
}

void pwmDeadTimeInit(
  EFR32PwmInstance *inst,
  EFR32PwmDeadTimeConfig *config
  )
{
  if (!inst || !config) {
    return;
  }

  // Enable Timer Clock
  sl_peripheral_t timerPeripheral = _getTimerPeripheral(inst->h.timer);
  if (NULL == timerPeripheral) {
    return;
  }
  sl_clock_manager_enable_bus_clock(timerPeripheral->bus_clock);

  uint32_t timer_frequency = 0;
  sl_clock_manager_get_clock_branch_frequency(timerPeripheral->clk_branch, &timer_frequency);
  unsigned int dtiTime = (timer_frequency / 1e3f) * config->deadTimeNs / 1e6f;
  if (dtiTime > 64) {
    dtiTime = SILABBS_DEFAULT_DEAD_TIME;
  }

  sl_hal_timer_dti_init_t initDTI = SL_HAL_TIMER_DTI_INIT_DEFAULT;
  initDTI.rise_time = dtiTime;
  initDTI.fall_time = dtiTime;
  initDTI.output_gen_mask = config->outputMask;

  sl_hal_timer_dti_init(inst->h.timer, &initDTI);
  sl_hal_timer_dti_enable(inst->h.timer);
}
