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

#include "Arduino.h"
#include "pins_arduino.h"
#include "pinDefinitions.h"

void pinMode(pin_size_t pinNumber, PinMode mode)
{
  PinName pin_name = pinToPinName(pinNumber);
  if (pin_name == PIN_NAME_NC) {
    return;
  }
  pinMode(pin_name, mode);
}

void pinMode(PinName pinNumber, PinMode pinMode)
{
  if (!get_system_init_finished() || pinNumber >= PIN_NAME_MAX) {
    return;
  }
  sl_gpio_t hw_gpio;
  hw_gpio.port = (uint8_t)getSilabsPortFromArduinoPin(pinNumber);
  hw_gpio.pin = getSilabsPinFromArduinoPin(pinNumber);
  switch (pinMode) {
    case PinMode::OUTPUT:
      sl_gpio_set_pin_mode(&hw_gpio, SL_GPIO_MODE_PUSH_PULL, false);
      break;

    case PinMode::INPUT:
      sl_gpio_set_pin_mode(&hw_gpio, SL_GPIO_MODE_INPUT, false);
      break;

    case PinMode::INPUT_PULLUP:
      sl_gpio_set_pin_mode(&hw_gpio, SL_GPIO_MODE_INPUT_PULL, true);
      break;

    default:
      break;
  }
}

PinStatus digitalRead(pin_size_t pinNumber)
{
  PinName pin_name = pinToPinName(pinNumber);
  if (pin_name == PIN_NAME_NC) {
    return PinStatus::LOW;
  }
  return digitalRead(pin_name);
}

PinStatus digitalRead(PinName pinNumber)
{
  if (!get_system_init_finished() || pinNumber >= PIN_NAME_MAX) {
    return PinStatus::LOW;
  }
  bool pin_value;
  sl_gpio_t hw_gpio;
  hw_gpio.port = (uint8_t)getSilabsPortFromArduinoPin(pinNumber);
  hw_gpio.pin = getSilabsPinFromArduinoPin(pinNumber);
  sl_gpio_get_pin_input(&hw_gpio, &pin_value);
  return pin_value ? PinStatus::HIGH : PinStatus::LOW;
}

void digitalWrite(pin_size_t pinNumber, PinStatus status)
{
  PinName actual_pin = pinToPinName(pinNumber);
  if (actual_pin == PIN_NAME_NC) {
    return;
  }
  digitalWrite(actual_pin, status);
}

void digitalWrite(PinName pinNumber, PinStatus status)
{
  if (!get_system_init_finished() || pinNumber >= PIN_NAME_MAX) {
    return;
  }
  sl_gpio_t out_gpio;
  out_gpio.port = (uint8_t)getSilabsPortFromArduinoPin(pinNumber);
  out_gpio.pin = getSilabsPinFromArduinoPin(pinNumber);
  if (status == PinStatus::LOW) {
    sl_gpio_clear_pin(&out_gpio);
  } else {
    sl_gpio_set_pin(&out_gpio);
  }
}
