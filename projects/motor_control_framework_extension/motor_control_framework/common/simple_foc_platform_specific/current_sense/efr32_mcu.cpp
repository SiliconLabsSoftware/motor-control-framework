/***************************************************************************//**
 * @file efr32_mcu.cpp
 * @brief EFR32 MCU specific current sense functions
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
#include <pins_arduino.h>

#include "efr32_mcu.h"
#include "sl_hal_prs.h"
#include "../driver/efr32_mcu.h"

#ifndef _ADC_VOLTAGE
#define _ADC_VOLTAGE 3.3f
#endif

#ifndef _ADC_RESOLUTION
#define _ADC_RESOLUTION 4095.0f
#endif

#ifndef _CLK_SRC_ADC_FREQ
#define _CLK_SRC_ADC_FREQ 20000000
#endif

#ifndef _CLK_ADC_FREQ
#define _CLK_ADC_FREQ 10000000
#endif

#ifndef SILABS_DEFAULT_MAX_CURRENT_SENSE_COUNT
#define SILABS_DEFAULT_MAX_CURRENT_SENSE_COUNT 2
#endif

extern void _getPrsUnderflowSignal(TIMER_TypeDef *timer, uint32_t *signal);

static EFR32CurrentSenseParams current_sense_params[SILABS_DEFAULT_MAX_CURRENT_SENSE_COUNT];
static uint8_t current_sense_params_index = 0;

static void _adcBusAllocate(
  uint8_t port,
  uint8_t pin
  )
{
  switch (port) {
#if (GPIO_PA_COUNT > 0)
    case gpioPortA:
      if (0 == pin % 2) {
        if ((GPIO->ABUSALLOC & _GPIO_ABUSALLOC_AEVEN0_MASK) == GPIO_ABUSALLOC_AEVEN0_TRISTATE) {
          GPIO->ABUSALLOC |= GPIO_ABUSALLOC_AEVEN0_ADC0;
        } else if ((GPIO->ABUSALLOC & _GPIO_ABUSALLOC_AEVEN1_MASK) == GPIO_ABUSALLOC_AEVEN1_TRISTATE) {
          GPIO->ABUSALLOC |= GPIO_ABUSALLOC_AEVEN1_ADC0;
        } else {
          // MISRA
        }
      } else {
        if ((GPIO->ABUSALLOC & _GPIO_ABUSALLOC_AODD0_MASK) == GPIO_ABUSALLOC_AODD0_TRISTATE) {
          GPIO->ABUSALLOC |= GPIO_ABUSALLOC_AODD0_ADC0;
        } else if ((GPIO->ABUSALLOC & _GPIO_ABUSALLOC_AODD1_MASK) == GPIO_ABUSALLOC_AODD1_TRISTATE) {
          GPIO->ABUSALLOC |= GPIO_ABUSALLOC_AODD1_ADC0;
        } else {
          // MISRA
        }
      }
      break;
#endif

#if (GPIO_PB_COUNT > 0)
    case gpioPortB:
      if (0 == pin % 2) {
        if ((GPIO->BBUSALLOC & _GPIO_BBUSALLOC_BEVEN0_MASK) == GPIO_BBUSALLOC_BEVEN0_TRISTATE) {
          GPIO->BBUSALLOC |= GPIO_BBUSALLOC_BEVEN0_ADC0;
        } else if ((GPIO->BBUSALLOC & _GPIO_BBUSALLOC_BEVEN1_MASK) == GPIO_BBUSALLOC_BEVEN1_TRISTATE) {
          GPIO->BBUSALLOC |= GPIO_BBUSALLOC_BEVEN1_ADC0;
        } else {
          // MISRA
        }
      } else {
        if ((GPIO->BBUSALLOC & _GPIO_BBUSALLOC_BODD0_MASK) == GPIO_BBUSALLOC_BODD0_TRISTATE) {
          GPIO->BBUSALLOC |= GPIO_BBUSALLOC_BODD0_ADC0;
        } else if ((GPIO->BBUSALLOC & _GPIO_BBUSALLOC_BODD1_MASK) == GPIO_BBUSALLOC_BODD1_TRISTATE) {
          GPIO->BBUSALLOC |= GPIO_BBUSALLOC_BODD1_ADC0;
        } else {
          // MISRA
        }
      }
      break;
#endif

#if (GPIO_PC_COUNT > 0 || GPIO_PD_COUNT > 0)
    case gpioPortC:
    case gpioPortD:
      if (0 == pin % 2) {
        if ((GPIO->CDBUSALLOC & _GPIO_CDBUSALLOC_CDEVEN0_MASK) == GPIO_CDBUSALLOC_CDEVEN0_TRISTATE) {
          GPIO->CDBUSALLOC |= GPIO_CDBUSALLOC_CDEVEN0_ADC0;
        } else if ((GPIO->CDBUSALLOC & _GPIO_CDBUSALLOC_CDEVEN1_MASK) == GPIO_CDBUSALLOC_CDEVEN1_TRISTATE) {
          GPIO->CDBUSALLOC |= GPIO_CDBUSALLOC_CDEVEN1_ADC0;
        } else {
          // MISRA
        }
      } else {
        if ((GPIO->CDBUSALLOC & _GPIO_CDBUSALLOC_CDODD0_MASK) == GPIO_CDBUSALLOC_CDODD0_TRISTATE) {
          GPIO->CDBUSALLOC |= GPIO_CDBUSALLOC_CDODD0_ADC0;
        } else if ((GPIO->CDBUSALLOC & _GPIO_CDBUSALLOC_CDODD1_MASK) == GPIO_CDBUSALLOC_CDODD1_TRISTATE) {
          GPIO->CDBUSALLOC |= GPIO_CDBUSALLOC_CDODD1_ADC0;
        } else {
          // MISRA
        }
      }
      break;
#endif

    default:
      // MISRA
      break;
  }
}

static void _adcConfig(
  EFR32AdcInstance *inst,
  const int pin
  )
{
  if (!inst) {
    return;
  }
  inst->port = getSilabsPortFromArduinoPin(pinToPinName(pin));
  inst->pin = getSilabsPinFromArduinoPin(pinToPinName(pin));
}

static float _readAdc(
  EFR32CurrentSenseParams *params,
  const int pin
  )
{
  if (!params) {
    return 0.0f;
  }

  for (uint8_t i = 0; i < SILABS_MAX_ANALOG; ++i) {
    if (!_isset(params->pins[i])) {
      continue;
    }
    if (pin == params->pins[i]) {
      return params->buffer[i] * params->adc_voltage_conv;
    }
  }
  return 0.0f;
}

static bool _dmaTransferFinishedCb(
  unsigned int channel,
  unsigned int sequenceNo,
  void *data
  )
{
  _UNUSED(sequenceNo);

  EFR32CurrentSenseParams *params = (EFR32CurrentSenseParams *) data;
  if (!params || !params->adc || (params->dmaChannel != channel)) {
    return false;
  }

  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_ATOMIC();
  params->dataReady = true;
  CORE_EXIT_ATOMIC();

  return false;
}

static void _currentSenseInitDMA(
  EFR32CurrentSenseParams *params,
  DMADRV_Callback_t fn,
  void *data
  )
{
  (void)data;
  if (!params) {
    return;
  }

  // Initialize DMA with default parameters
  DMADRV_Init();

  DMADRV_AllocateChannel(&params->dmaChannel, NULL);

  // Trigger LDMA transfer on IADC scan completion
  LDMA_TransferCfg_t transferCfg =
    LDMA_TRANSFER_CFG_PERIPHERAL(ldmaPeripheralSignal_IADC0_IADC_SCAN);

  params->descriptor =
    (LDMA_Descriptor_t)LDMA_DESCRIPTOR_LINKREL_P2M_WORD(&(params->adc->SCANFIFODATA),
                                                        params->buffer,
                                                        params->noAdcChannels,
                                                        0);

  DMADRV_LdmaStartTransfer(params->dmaChannel,
                           &transferCfg,
                           &params->descriptor,
                           fn,
                           params);
}

static void _currentSenseInitScan(
  EFR32CurrentSenseParams *params
  )
{
  if (!params || !params->adc) {
    return;
  }

  // Enable Clock
  sl_clock_manager_enable_bus_clock(SL_BUS_CLOCK_IADC0);
  sl_clock_manager_enable_bus_clock(SL_BUS_CLOCK_GPIO);

  // Use the FSRC0 as the IADC clock so it can run in EM2
  // The sl_clock_manager is designed around static,
  // compile-time clock tree configuration rather than dynamic runtime switching like the older EMLib API.
  // This is by design for safety and performance reasons."

  for (uint8_t i = 0; i < params->noAdcChannels; ++i) {
    sl_gpio_t gpio = {
      .port = params->inst[i].port,
      .pin = params->inst[i].pin
    };
    sl_gpio_set_pin_mode(&gpio, SL_GPIO_MODE_DISABLED, false);
  }

  sl_hal_iadc_init_t init = SL_HAL_IADC_INIT_DEFAULT;
  init.warmup = SL_HAL_IADC_WARMUP_KEEP_WARM;
  init.src_clk_prescale = sl_hal_iadc_calculate_src_clk_prescale(params->adc, _CLK_SRC_ADC_FREQ, 0);

  sl_hal_iadc_voltage_reference_t adcRef;
  switch (params->vRef) {
    case 1200: adcRef = SL_HAL_IADC_REFERENCE_VREFINT_1V2; break;
    case 1250: adcRef = SL_HAL_IADC_VREF_EXT_1V25; break;
    case 3300: adcRef = SL_HAL_IADC_VREF_VDDX; break;
    case 2640: adcRef = SL_HAL_IADC_VREF_VDDX0P8BUF; break;
    default: return;
  }

  init.configs[0].reference = adcRef;
  init.configs[0].vref = params->vRef;
  init.configs[0].adc_clk_prescale = sl_hal_iadc_calculate_adc_clk_prescale(params->adc,
                                                                            _CLK_ADC_FREQ,
                                                                            0,
                                                                            SL_HAL_IADC_CFG_ADC_MODE_NORMAL,
                                                                            init.src_clk_prescale);

  // Reset the ADC
  sl_hal_iadc_reset(params->adc);

  // Only configure the ADC if it is not already running
  if (params->adc->CTRL == _IADC_CTRL_RESETVALUE) {
    uint32_t iadc_freq;
    sl_clock_manager_get_clock_branch_frequency(SL_CLOCK_BRANCH_IADCCLK, &iadc_freq);
    sl_hal_iadc_init(params->adc, &init, iadc_freq);
    sl_hal_iadc_enable(params->adc);
    sl_hal_iadc_wait_sync(params->adc);
  }

  sl_hal_iadc_init_scan_t initScan = SL_HAL_IADC_INITSCAN_DEFAULT;
  if ((params->mode == CS_LO_SIDE) || (params->mode == CS_HI_SIDE)) {
    // Note: CS_HI_SIDE not implemented
    initScan.trigger_select = SL_HAL_IADC_TRIGGER_PRSPOS;
  }
  initScan.fifo_dma_wakeup = true;

  sl_hal_iadc_scan_table_t scanTable = SL_HAL_IADC_SCANTABLE_DEFAULT;
  for (uint8_t i = 0; i < params->noAdcChannels; ++i) {
    sl_gpio_t gpio = {
      .port = params->inst[i].port,
      .pin = params->inst[i].pin
    };
    scanTable.entries[i].positive_port = sl_hal_iadc_port_pin_to_pos_port(&gpio);
    scanTable.entries[i].positive_pin = params->inst[i].pin;
    scanTable.entries[i].negative_port = SL_HAL_IADC_NEG_PORT_INPUT_GND;
    scanTable.entries[i].negative_pin = SL_HAL_IADC_NEG_PIN_INPUT_GND;
    scanTable.entries[i].include_in_scan = true;
  }

  // Initialize IADC
  uint32_t iadc_freq;
  sl_clock_manager_get_clock_branch_frequency(SL_CLOCK_BRANCH_IADCCLK, &iadc_freq);
  sl_hal_iadc_init(params->adc, &init, iadc_freq);
  sl_hal_iadc_enable(params->adc);
  sl_hal_iadc_wait_sync(params->adc);

  // Initialize Scan
  sl_hal_iadc_init_scan(params->adc, &initScan, &scanTable);
  sl_hal_iadc_set_scan_mask_multiple_entries(params->adc, &scanTable);

  // Enable IADC before issuing commands or starting DMA
  sl_hal_iadc_enable(params->adc);
  sl_hal_iadc_wait_sync(params->adc);

  // Allocate
  for (uint8_t i = 0; i < params->noAdcChannels; ++i) {
    _adcBusAllocate(params->inst[i].port, params->inst[i].pin);
  }
}

static void _currentSenseConfig(
  EFR32CurrentSenseParams *params,
  int adcPins[SILABS_MAX_ANALOG]
  )
{
  if (!params) {
    return;
  }

  uint8_t noAdcChannels = 0;
  for (int i = 0; i < SILABS_MAX_ANALOG; ++i) {
    if (!_isset(adcPins[i])) {
      continue;
    }
    if (params->firstIndex == 0xFF) {
      params->firstIndex = i;
    }
    _adcConfig(&params->inst[noAdcChannels], adcPins[i]);
    params->pins[noAdcChannels] = adcPins[i];
    ++noAdcChannels;
  }

  params->noAdcChannels = noAdcChannels;
}

static void _currentSenseDeinit(
  EFR32CurrentSenseParams *params
  )
{
  if (!params) {
    return;
  }

  DMADRV_StopTransfer(params->dmaChannel);
  DMADRV_FreeChannel(params->dmaChannel);

  sl_hal_iadc_reset(params->adc);
}

static void _currentSenseStartScan(
  EFR32CurrentSenseParams *params
  )
{
  if (!params || !params->adc) {
    return;
  }

  // Ensure IADC is enabled before issuing a command (avoid bus fault/assert)
  if ((params->adc->EN & _IADC_EN_EN_MASK) == 0) {
    sl_hal_iadc_enable(params->adc);
    sl_hal_iadc_wait_sync(params->adc);
  }

  sl_hal_iadc_start_scan(params->adc);
}

static void _currentSenseStopScan(
  EFR32CurrentSenseParams *params
  )
{
  if (!params) {
    return;
  }

  sl_hal_iadc_stop_scan(params->adc);
}

static void _currentSenseStopTranfer(
  EFR32CurrentSenseParams *params
  )
{
  if (!params || !params->adc) {
    return;
  }

  DMADRV_PauseTransfer(params->dmaChannel);
}

static void _currentSenseStartTranfer(
  EFR32CurrentSenseParams *params
  )
{
  if (!params || !params->adc) {
    return;
  }

  DMADRV_ResumeTransfer(params->dmaChannel);
}

////////////////////////////////////////////////////////////////////////////////
// Low Side Mode
////////////////////////////////////////////////////////////////////////////////

float _readADCVoltageLowSide(
  const int pin,
  const void *cs_params
  )
{
  EFR32CurrentSenseParams *params = (EFR32CurrentSenseParams *) cs_params;
  if (!params) {
    return 0.0f;
  }

  return _readAdc(params, pin);
}

void* _configureADCLowSide(
  const void* driver_params,
  const int pinA,
  const int pinB,
  const int pinC
  )
{
  _UNUSED(driver_params);

  if (current_sense_params_index >= SILABS_DEFAULT_MAX_CURRENT_SENSE_COUNT) {
    return SIMPLEFOC_CURRENT_SENSE_INIT_FAILED;
  }

  EFR32CurrentSenseParams *params = &current_sense_params[current_sense_params_index++];
  *params = (EFR32CurrentSenseParams) {
    .adc_voltage_conv = _ADC_VOLTAGE / _ADC_RESOLUTION,
    .firstIndex = 0xFF,
    .noAdcChannels = 0,
    .vRef = SILABS_ADC_VREF,
    .prsChannel = SILABS_ADC_PRS_CHANNEL,
    .mode = CS_LO_SIDE,
    .adc = SILABS_DEFAULT_ADC_PERPHERAL,
  };

  if (!params) {
    return SIMPLEFOC_CURRENT_SENSE_INIT_FAILED;
  }

  int adcPins[3] = { pinA, pinB, pinC };

  _currentSenseConfig(params, adcPins);
  _currentSenseInitScan(params);
  _currentSenseInitDMA(params, NULL, params);
  _currentSenseStartScan(params);

  return params;
}

void* _driverSyncLowSide(
  void *driver_params,
  void *cs_params
  )
{
  EFR32DriverParams *driver = (EFR32DriverParams *) driver_params;
  EFR32CurrentSenseParams *params = (EFR32CurrentSenseParams *) cs_params;

  if (!driver || !params) {
    return SIMPLEFOC_CURRENT_SENSE_INIT_FAILED;
  }

  uint32_t prsSignal;

  sl_clock_manager_enable_bus_clock(SL_BUS_CLOCK_PRS);

  _getPrsUnderflowSignal(driver->inst[0].h.timer, &prsSignal);
  sl_hal_prs_async_connect_channel_producer(params->prsChannel, prsSignal);
  sl_hal_prs_connect_channel_consumer(params->prsChannel, SL_HAL_PRS_TYPE_ASYNC, SL_HAL_PRS_CONSUMER_IADC0_SCANTRIGGER);

  return cs_params;
}

////////////////////////////////////////////////////////////////////////////////
// Inline Mode
////////////////////////////////////////////////////////////////////////////////

float _readADCVoltageInline(
  const int pin,
  const void *cs_params
  )
{
  EFR32CurrentSenseParams *params = (EFR32CurrentSenseParams *) cs_params;
  if (!params || !_isset(pin) || (params->firstIndex == 0xFF)) {
    return 0.0f;
  }

  if (params->pins[params->firstIndex] == pin) {
    CORE_DECLARE_IRQ_STATE;
    CORE_ENTER_ATOMIC();
    params->dataReady = false;
    CORE_EXIT_ATOMIC();

    _currentSenseStartScan(params);

    while (!params->dataReady) {
      // Wait for data to be ready
    }
  }

  return _readAdc(params, pin);
}

void* _configureADCInline(
  const void* driver_params,
  const int pinA,
  const int pinB,
  const int pinC
  )
{
  _UNUSED(driver_params);

  if (current_sense_params_index >= SILABS_DEFAULT_MAX_CURRENT_SENSE_COUNT) {
    return SIMPLEFOC_CURRENT_SENSE_INIT_FAILED;
  }

  EFR32CurrentSenseParams *params = &current_sense_params[current_sense_params_index++];
  *params = (EFR32CurrentSenseParams) {
    .adc_voltage_conv = _ADC_VOLTAGE / _ADC_RESOLUTION,
    .firstIndex = 0xFF,
    .noAdcChannels = 0,
    .vRef = SILABS_ADC_VREF,
    .prsChannel = SILABS_ADC_PRS_CHANNEL,
    .mode = CS_INLINE,
    .adc = SILABS_DEFAULT_ADC_PERPHERAL,
  };

  if (!params) {
    return SIMPLEFOC_CURRENT_SENSE_INIT_FAILED;
  }

  int adcPins[3] = { pinA, pinB, pinC };

  _currentSenseConfig(params, adcPins);
  _currentSenseInitScan(params);
  _currentSenseInitDMA(params, _dmaTransferFinishedCb, params);

  return params;
}
