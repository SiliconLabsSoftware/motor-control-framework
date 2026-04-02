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

#include "adc.h"

using namespace arduino;

static bool dma_transfer_finished_cb(unsigned int channel, unsigned int sequenceNo, void *userParam);

AdcClass::AdcClass() :
  initialized_single(false),
  initialized_scan(false),
  paused_transfer(false),
  current_adc_pin(PD2),
  current_adc_reference(AR_VDD),
  current_read_resolution(this->max_read_resolution_bits),
  user_onsampling_finished_callback(nullptr),
  adc_mutex(nullptr)
{
  this->adc_mutex = xSemaphoreCreateMutexStatic(&this->adc_mutex_buf);
  configASSERT(this->adc_mutex);
}

void AdcClass::init_single(PinName pin, uint8_t reference)
{
  // Set up the ADC pin as an input
  pinMode(pin, INPUT);

  // Create ADC init structs with default values
  sl_hal_iadc_init_t init = SL_HAL_IADC_INIT_DEFAULT;
  sl_hal_iadc_init_single_t init_single = SL_HAL_IADC_INITSINGLE_DEFAULT;
  sl_hal_iadc_single_input_t input = SL_HAL_IADC_SINGLEINPUT_DEFAULT;

  // Enable IADC0, GPIO and PRS clock branches
  sl_clock_manager_enable_bus_clock(SL_BUS_CLOCK_IADC0);
  sl_clock_manager_enable_bus_clock(SL_BUS_CLOCK_GPIO);
  sl_clock_manager_enable_bus_clock(SL_BUS_CLOCK_PRS);

  sl_hal_iadc_voltage_reference_t sl_adc_reference;
  uint32_t sl_adc_vref;

  // Set the voltage reference
  switch (reference) {
    case AR_INTERNAL1V2:
      sl_adc_reference = SL_HAL_IADC_REFERENCE_VREFINT_1V2;
      sl_adc_vref = 1200;
      break;

    case AR_EXTERNAL_1V25:
      sl_adc_reference = SL_HAL_IADC_VREF_EXT_1V25;
      sl_adc_vref = 1250;
      break;

    case AR_VDD:
      sl_adc_reference = SL_HAL_IADC_VREF_VDDX;
      sl_adc_vref = 3300;
      break;

    case AR_08VDD:
      sl_adc_reference = SL_HAL_IADC_VREF_VDDX0P8BUF;
      sl_adc_vref = 2640;
      break;

    default:
      return;
  }
  init.configs[0].reference = sl_adc_reference;
  init.configs[0].vref = sl_adc_vref;

  // Reset the ADC
  sl_hal_iadc_reset(IADC0);

  // Only configure the ADC if it is not already running
  if (IADC0->CTRL == _IADC_CTRL_RESETVALUE) {
    uint32_t iadc_freq;
    sl_clock_manager_get_clock_branch_frequency(SL_CLOCK_BRANCH_IADCCLK, &iadc_freq);
    sl_hal_iadc_init(IADC0, &init, iadc_freq);
  }

  // Assign the input pin
  uint32_t pin_index = pin - PIN_NAME_MIN;
  input.positive_port = GPIO_to_ADC_pin_map[pin_index].port;
  input.positive_pin = GPIO_to_ADC_pin_map[pin_index].pin;

  // Initialize the ADC
  sl_hal_iadc_init_single(IADC0, &init_single, &input);
  sl_hal_iadc_enable_interrupts(IADC0, IADC_IEN_SINGLEDONE);

  // Allocate the analog bus for ADC0 inputs
  // Port C and D are handled together
  // Even and odd pins on the same port have a different register value
  bool pin_is_even = (pin % 2 == 0);
  if (pin >= PD0 || pin >= PC0) {
    if (pin_is_even) {
      GPIO->CDBUSALLOC |= GPIO_CDBUSALLOC_CDEVEN0_ADC0;
    } else {
      GPIO->CDBUSALLOC |= GPIO_CDBUSALLOC_CDODD0_ADC0;
    }
  } else if (pin >= PB0) {
    if (pin_is_even) {
      GPIO->BBUSALLOC |= GPIO_BBUSALLOC_BEVEN0_ADC0;
    } else {
      GPIO->BBUSALLOC |= GPIO_BBUSALLOC_BODD0_ADC0;
    }
  } else {
    if (pin_is_even) {
      GPIO->ABUSALLOC |= GPIO_ABUSALLOC_AEVEN0_ADC0;
    } else {
      GPIO->ABUSALLOC |= GPIO_ABUSALLOC_AODD0_ADC0;
    }
  }

  this->initialized_scan = false;
  this->initialized_single = true;
}

void AdcClass::init_scan(PinName pin, uint8_t reference)
{
  // Set up the ADC pin as an input
  pinMode(pin, INPUT);

  // Create ADC init structs with default values
  sl_hal_iadc_init_t init = SL_HAL_IADC_INIT_DEFAULT;
  sl_hal_iadc_init_scan_t init_scan = SL_HAL_IADC_INITSCAN_DEFAULT;

  // Scan table structure
  sl_hal_iadc_scan_table_t scanTable = SL_HAL_IADC_SCANTABLE_DEFAULT;

  // Enable IADC0, GPIO and PRS clock branches
  sl_clock_manager_enable_bus_clock(SL_BUS_CLOCK_IADC0);
  sl_clock_manager_enable_bus_clock(SL_BUS_CLOCK_GPIO);
  sl_clock_manager_enable_bus_clock(SL_BUS_CLOCK_PRS);

  // Shutdown between conversions to reduce current
  init.warmup = SL_HAL_IADC_WARMUP_NORMAL;

  // Set the HFSCLK prescale value here
  init.src_clk_prescale = sl_hal_iadc_calculate_src_clk_prescale(IADC0, ADC_SRC_CLK_FREQ_HZ, 0);

  sl_hal_iadc_voltage_reference_t sl_adc_reference;
  uint32_t sl_adc_vref;

  // Set the voltage reference
  switch (reference) {
    case AR_INTERNAL1V2:
      sl_adc_reference = SL_HAL_IADC_REFERENCE_VREFINT_1V2;
      sl_adc_vref = 1200;
      break;

    case AR_EXTERNAL_1V25:
      sl_adc_reference = SL_HAL_IADC_VREF_EXT_1V25;
      sl_adc_vref = 1250;
      break;

    case AR_VDD:
      sl_adc_reference = SL_HAL_IADC_VREF_VDDX;
      sl_adc_vref = 3300;
      break;

    case AR_08VDD:
      sl_adc_reference = SL_HAL_IADC_VREF_VDDX0P8BUF;
      sl_adc_vref = 2640;
      break;

    default:
      return;
  }

  // Set the voltage reference
  init.configs[0].reference = sl_adc_reference;
  init.configs[0].vref = sl_adc_vref;
  init.configs[0].osr_high_speed = SL_HAL_IADC_OSR_HIGH_SPEED_2X;
  init.configs[0].analog_gain = SL_HAL_IADC_ANALOG_GAIN_1;

  /*
   * CLK_SRC_ADC must be prescaled by some value greater than 1 to
   * derive the intended CLK_ADC frequency.
   * Based on the default 2x oversampling rate (OSRHS)...
   * conversion time = ((4 * OSRHS) + 2) / fCLK_ADC
   * ...which results in a maximum sampling rate of 833 ksps with the
   * 2-clock input multiplexer switching time is included.
   */
  init.configs[0].adc_clk_prescale = sl_hal_iadc_calculate_adc_clk_prescale(IADC0,
                                                                            10000000,
                                                                            0,
                                                                            IADC_CFG_ADCMODE_NORMAL,
                                                                            init.src_clk_prescale);

  // Reset the ADC
  sl_hal_iadc_reset(IADC0);

  // Only configure the ADC if it is not already running
  if (IADC0->CTRL == _IADC_CTRL_RESETVALUE) {
    uint32_t iadc_freq;
    sl_clock_manager_get_clock_branch_frequency(SL_CLOCK_BRANCH_IADCCLK, &iadc_freq);
    sl_hal_iadc_init(IADC0, &init, iadc_freq);
  }

  // Assign the input pin
  uint32_t pin_index = pin - PIN_NAME_MIN;

  // Trigger continuously once scan is started
  init_scan.trigger_action = SL_HAL_IADC_TRIGGER_ACTION_CONTINUOUS;
  // Set the SCANFIFODVL flag when scan FIFO holds 2 entries
  // The interrupt associated with the SCANFIFODVL flag in the IADC_IF register is not used
  init_scan.data_valid_level = SL_HAL_IADC_DATA_VALID_1;
  // Enable DMA wake-up to save the results when the specified FIFO level is hit
  init_scan.fifo_dma_wakeup = true;

  scanTable.entries[0].positive_port = GPIO_to_ADC_pin_map[pin_index].port;
  scanTable.entries[0].positive_pin = GPIO_to_ADC_pin_map[pin_index].pin;
  scanTable.entries[0].include_in_scan = true;

  // Initialize scan
  sl_hal_iadc_init_scan(IADC0, &init_scan, &scanTable);
  sl_hal_iadc_enable_interrupts(IADC0, IADC_IEN_SCANTABLEDONE);

  // Allocate the analog bus for ADC0 inputs
  // Port C and D are handled together
  // Even and odd pins on the same port have a different register value
  bool pin_is_even = (pin % 2 == 0);
  if (pin >= PD0 || pin >= PC0) {
    if (pin_is_even) {
      GPIO->CDBUSALLOC |= GPIO_CDBUSALLOC_CDEVEN0_ADC0;
    } else {
      GPIO->CDBUSALLOC |= GPIO_CDBUSALLOC_CDODD0_ADC0;
    }
  } else if (pin >= PB0) {
    if (pin_is_even) {
      GPIO->BBUSALLOC |= GPIO_BBUSALLOC_BEVEN0_ADC0;
    } else {
      GPIO->BBUSALLOC |= GPIO_BBUSALLOC_BODD0_ADC0;
    }
  } else {
    if (pin_is_even) {
      GPIO->ABUSALLOC |= GPIO_ABUSALLOC_AEVEN0_ADC0;
    } else {
      GPIO->ABUSALLOC |= GPIO_ABUSALLOC_AODD0_ADC0;
    }
  }

  this->initialized_single = false;
  this->initialized_scan = true;
}

sl_status_t AdcClass::init_dma(uint32_t *buffer, uint32_t size)
{
  sl_status_t status;
  if (!this->initialized_scan) {
    return SL_STATUS_NOT_INITIALIZED;
  }

  // Initialize DMA with default parameters
  DMADRV_Init();

  // Allocate DMA channel
  status = DMADRV_AllocateChannel(&this->dma_channel, NULL);
  if (status != ECODE_EMDRV_DMADRV_OK) {
    return SL_STATUS_FAIL;
  }

  // Trigger LDMA transfer on IADC scan completion
  LDMA_TransferCfg_t transferCfg = LDMA_TRANSFER_CFG_PERIPHERAL(ldmaPeripheralSignal_IADC0_IADC_SCAN);

  /*
   * Set up a linked descriptor to save scan results to the
   * user-specified buffer. By linking the descriptor to itself
   * (the last argument is the relative jump in terms of the number of
   * descriptors), transfers will run continuously.
   */
  #pragma GCC diagnostic ignored "-Wmissing-field-initializers"
  this->ldma_descriptor = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_LINKREL_P2M_WORD(&(IADC0->SCANFIFODATA), buffer, size, 0);

  DMADRV_LdmaStartTransfer((int)this->dma_channel, &transferCfg, &this->ldma_descriptor, dma_transfer_finished_cb, NULL);
  return SL_STATUS_OK;
}

uint16_t AdcClass::get_sample(PinName pin)
{
  xSemaphoreTake(this->adc_mutex, portMAX_DELAY);

  if (this->initialized_scan) {
    this->scan_stop();
  }

  if (!this->initialized_single || (pin != this->current_adc_pin)) {
    this->current_adc_pin = pin;
    this->init_single(this->current_adc_pin, this->current_adc_reference);
  }
  // Clear single done interrupt
  sl_hal_iadc_clear_interrupts(IADC0, IADC_IF_SINGLEDONE);

  // Start conversion and wait for result
  sl_hal_iadc_set_command(IADC0, SL_HAL_IADC_CMD_START_SINGLE);
  while (!(sl_hal_iadc_get_pending_interrupts(IADC0) & IADC_IF_SINGLEDONE)) {
    yield();
  }
  uint16_t result = sl_hal_iadc_read_single_data(IADC0);

  xSemaphoreGive(this->adc_mutex);

  // Apply the configured read resolution
  result = result >> (this->max_read_resolution_bits - this->current_read_resolution);

  return result;
}

void AdcClass::set_reference(uint8_t reference)
{
  if (reference >= AR_MAX || reference == this->current_adc_reference) {
    return;
  }
  xSemaphoreTake(this->adc_mutex, portMAX_DELAY);
  this->current_adc_reference = reference;
  if (this->initialized_single) {
    this->init_single(this->current_adc_pin, this->current_adc_reference);
  } else if (this->initialized_scan) {
    this->init_scan(this->current_adc_pin, this->current_adc_reference);
  }
  xSemaphoreGive(this->adc_mutex);
}

void AdcClass::set_read_resolution(uint8_t resolution)
{
  if (resolution > this->max_read_resolution_bits) {
    this->current_read_resolution = this->max_read_resolution_bits;
    return;
  }
  this->current_read_resolution = resolution;
}

sl_status_t AdcClass::scan_start(PinName pin, uint32_t *buffer, uint32_t size, void (*user_onsampling_finished_callback)())
{
  sl_status_t status = SL_STATUS_FAIL;
  xSemaphoreTake(this->adc_mutex, portMAX_DELAY);

  if ((!this->initialized_scan && !this->initialized_single) || (pin != this->current_adc_pin)) {
    // Initialize in scan mode
    this->current_adc_pin = pin;
    this->user_onsampling_finished_callback = user_onsampling_finished_callback;
    this->init_scan(this->current_adc_pin, this->current_adc_reference);
    status = this->init_dma(buffer, size);
  } else if (this->initialized_scan && this->paused_transfer) {
    // Resume DMA transfer if paused
    status = DMADRV_ResumeTransfer(this->dma_channel);
    this->paused_transfer = false;
  } else if (this->initialized_single) {
    // Initialize in scan mode if it was initialized in single mode
    this->deinit();
    this->current_adc_pin = pin;
    this->user_onsampling_finished_callback = user_onsampling_finished_callback;
    this->init_scan(this->current_adc_pin, this->current_adc_reference);
    status = this->init_dma(buffer, size);
  } else {
    xSemaphoreGive(this->adc_mutex);
    return status;
  }

  // Start the conversion and wait for results
  sl_hal_iadc_set_command(IADC0, SL_HAL_IADC_CMD_START_SCAN);

  xSemaphoreGive(this->adc_mutex);
  return status;
}

void AdcClass::scan_stop()
{
  // Pause sampling
  DMADRV_PauseTransfer(this->dma_channel);
  this->paused_transfer = true;
}

void AdcClass::deinit()
{
  // Stop sampling
  DMADRV_StopTransfer(this->dma_channel);

  // Free resources
  DMADRV_FreeChannel(this->dma_channel);

  // Reset the ADC
  sl_hal_iadc_reset(IADC0);

  this->initialized_scan = false;
  this->initialized_single = false;
  this->current_adc_pin = PIN_NAME_NC;
}

void AdcClass::handle_dma_finished_callback()
{
  if (!this->user_onsampling_finished_callback) {
    return;
  }

  this->user_onsampling_finished_callback();
}

static bool dma_transfer_finished_cb(unsigned int channel, unsigned int sequenceNo, void *userParam)
{
  (void)channel;
  (void)sequenceNo;
  (void)userParam;

  ADC.handle_dma_finished_callback();
  return false;
}

const IADC_PosInput_Map_t AdcClass::GPIO_to_ADC_pin_map[64] = {
  // Port A
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_A, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_0 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_A, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_1 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_A, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_2 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_A, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_3 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_A, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_4 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_A, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_5 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_A, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_6 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_A, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_7 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_A, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_8 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_A, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_9 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_A, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_10 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_A, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_11 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_A, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_12 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_A, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_13 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_A, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_14 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_A, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_15 },
  // Port B
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_B, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_0 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_B, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_1 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_B, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_2 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_B, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_3 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_B, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_4 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_B, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_5 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_B, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_6 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_B, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_7 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_B, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_8 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_B, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_9 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_B, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_10 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_B, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_11 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_B, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_12 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_B, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_13 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_B, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_14 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_B, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_15 },
  // Port C
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_C, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_0 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_C, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_1 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_C, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_2 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_C, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_3 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_C, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_4 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_C, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_5 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_C, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_6 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_C, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_7 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_C, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_8 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_C, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_9 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_C, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_10 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_C, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_11 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_C, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_12 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_C, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_13 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_C, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_14 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_C, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_15 },
  // Port D
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_D, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_0 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_D, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_1 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_D, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_2 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_D, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_3 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_D, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_4 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_D, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_5 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_D, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_6 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_D, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_7 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_D, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_8 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_D, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_9 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_D, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_10 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_D, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_11 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_D, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_12 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_D, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_13 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_D, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_14 },
  { SL_HAL_IADC_POS_PORT_INPUT_PORT_D, SL_HAL_IADC_GPIO_PORT_INPUT_PIN_15 }
};

arduino::AdcClass ADC;
