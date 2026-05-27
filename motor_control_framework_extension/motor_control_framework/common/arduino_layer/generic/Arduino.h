/*
 * This file is part of the Silicon Labs Arduino Core
 *
 * The MIT License (MIT)
 *
 * Copyright 2025 Silicon Laboratories Inc. www.silabs.com
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

#ifndef ARDUINO_H
#define ARDUINO_H

#include "api/ArduinoAPI.h"

using namespace arduino;

#include <cmath>
#include "FreeRTOS.h"
#include "task.h"
#include "arduino_variant.h"

extern "C" {
#include "sl_common.h"
#include "sl_sleeptimer.h"
// RMU has no HAL equivalent at this time
#include "em_rmu.h"
#include "sl_udelay.h"
#include "sl_core.h"
}

#include "pinDefinitions.h"
#include "pins_arduino.h"
#include "Serial.h"
#include "adc.h"
#include "overloads.h"

#ifdef NUM_DAC_HW
#include "dac.h"
#endif // NUM_DAC_HW

using std::round;
using std::isinf;
using std::isnan;
using std::min;
using std::max;
using std::abs;

/** @note State lives in Interrupt.cpp. SimpleFOC-compatible usage: thread/task context
 *        only; do not yield between them.
 *        Do not call noInterrupts()/interrupts() from an ISR - shared nesting state is not re-entrant. */
extern volatile uint32_t _foc_irq_nesting;
extern CORE_irqState_t _foc_irq_saved;

static inline void _foc_no_interrupts(void)
{
  CORE_irqState_t st = CORE_EnterCritical();
  if (_foc_irq_nesting == 0) {
    _foc_irq_saved = st;
  }
  _foc_irq_nesting++;
}

static inline void _foc_interrupts(void)
{
  if (_foc_irq_nesting == 0) {
    return;
  }
  if (--_foc_irq_nesting == 0) {
    CORE_ExitCritical(_foc_irq_saved);
  }
}

#define noInterrupts() _foc_no_interrupts()
#define interrupts() _foc_interrupts()

/***************************************************************************//**
 * Sets the DAC voltage reference
 * Possible values:
 *  - DAC_VREF_1V25
 *  - DAC_VREF_2V5,
 *  - DAC_VREF_AVDD,
 *  - DAC_VREF_EXTERNAL_PIN
 *
 * @param[in] reference The selected reference from 'dac_voltage_references'
 ******************************************************************************/
void analogReferenceDAC(uint8_t reference);

typedef enum _dac_channel_t dac_channel_t;
void analogWrite(dac_channel_t dac_channel, int value);
void analogWriteResolution(int resolution);
void analogReadResolution(int resolution);

/***************************************************************************//**
 * Starts continuous ADC sample acquisition using DMA
 *
 * @param[in] pin The selected analog input pin
 * @param[in] buffer Pointer to the sampling buffer
 * @param[in] size The size of the sampling buffer
 * @param[in] user_onsampling_finished_callback Callback that gets called when an
 *            acquisition finishes - pass 'nullptr' to stop sampling
 ******************************************************************************/
void analogReadDMA(PinName pin, uint32_t *buffer, uint32_t size, void (*user_onsampling_finished_callback)());
void analogReadDMA(pin_size_t pin, uint32_t *buffer, uint32_t size, void (*user_onsampling_finished_callback)());

bool get_system_init_finished();
void escape_hatch();
void gpio_interrupt_handler_init();
void arduino_layer_init();

#endif // ARDUINO_H
