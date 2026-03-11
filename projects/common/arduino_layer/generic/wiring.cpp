/*
 * This file is part of the Silicon Labs Arduino Core
 *
 * The MIT License (MIT)
 *
 * Copyright 2024 Silicon Laboratories Inc. www.silabs.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "pinDefinitions.h"
#include "pins_arduino.h"
#include "sl_hal_timer.h"
#include "sl_device_peripheral.h"

// The sleeptimer is running on a 32.768 kHz oscillator with a tick resolution of 30.52 us
static const double sleeptimer_tick_period_us = 30.52f;
static const uint64_t sleeptimer_tick_period_us_x100 = 3052;

uint32_t millis()
{
  uint64_t millis = 0u;
  (void)sl_sleeptimer_tick64_to_ms(sl_sleeptimer_get_tick_count64(), &millis);
  return static_cast < uint32_t > (millis);
}

uint32_t micros()
{
#if defined(ARDUINO_MICROS_TIMER_PERIPHERAL)
  TIMER_TypeDef *micros_timer = ((TIMER_TypeDef *)ARDUINO_MICROS_TIMER_PERIPHERAL->base);
  static bool micros_scaling_initialized = false;
  static uint64_t micros_scale_numerator = 0u;
  static uint32_t micros_scale_denominator = 1u;

  if (!micros_scaling_initialized) {
    // TIMER is set up: count rate = clk_freq / prescaler => time_us = counter * prescaler * 1e6 / clk_freq
    const uint32_t prescaler = ((micros_timer->CFG & _TIMER_CFG_PRESC_MASK) >> _TIMER_CFG_PRESC_SHIFT) + 1u;
    uint32_t clk_freq = 0u;
    sl_clock_manager_get_clock_branch_frequency(ARDUINO_MICROS_TIMER_PERIPHERAL->clk_branch, &clk_freq);
    if (clk_freq == 0u) {
      return 0u;
    }

    micros_scale_numerator = (uint64_t)prescaler * 1000000ULL;
    micros_scale_denominator = clk_freq;
    micros_scaling_initialized = true;
  }

  const uint32_t counter = sl_hal_timer_get_counter(micros_timer);
  return (uint32_t)((uint64_t)counter * micros_scale_numerator / (uint64_t)micros_scale_denominator);
#else
  // Fallback: sleeptimer-based microseconds (30.52us resolution)
  uint64_t us = static_cast < uint64_t > (sl_sleeptimer_get_tick_count()) * sleeptimer_tick_period_us_x100 / 100u;
  return static_cast < uint32_t > (us);
#endif
}

void delay(uint32_t ms)
{
  uint32_t div = portTICK_PERIOD_MS;
  if (div == 0) {
    div = 1;
  }
  const TickType_t xDelay = ms / div;
  vTaskDelay(xDelay);
}

void delayMicroseconds(unsigned int us)
{
  sl_udelay_wait(us);
}

void yield()
{
  taskYIELD();
}
