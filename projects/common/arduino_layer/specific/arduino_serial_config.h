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

// This file is an adapter between the different USART/EUSART instances and the Arduino Core driver
#ifndef ARDUINO_SERIAL_CONFIG_H
#define ARDUINO_SERIAL_CONFIG_H

// Configure Arduino Serial to use RTT iostream backend
#include "sl_iostream_rtt.h"
extern "C" {
  #include "sl_iostream_handles.h"
}

extern sl_iostream_t* sl_serial_stream_handle;
extern sl_iostream_t* sl_serial_instance_handle;
void sl_serial_set_baud_rate(uint32_t baudrate);
void sl_serial_init();
void sl_serial_deinit();

extern sl_iostream_t* sl_serial1_stream_handle;
extern sl_iostream_t* sl_serial1_instance_handle;
void sl_serial1_set_baud_rate(uint32_t baudrate);
void sl_serial1_init();
void sl_serial1_deinit();

#endif // ARDUINO_SERIAL_CONFIG_H
