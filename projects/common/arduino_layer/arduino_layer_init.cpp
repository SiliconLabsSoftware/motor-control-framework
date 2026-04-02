/***************************************************************************//**
 * @file
 * @brief Arduino layer initialization
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
#include "generic/Arduino.h"

static bool system_init_finished = false;

void arduino_layer_init()
{
  init_arduino_variant();
  system_init_finished = true;

  escape_hatch();
  gpio_interrupt_handler_init();
}

bool get_system_init_finished()
{
  return system_init_finished;
}

SL_WEAK void escape_hatch()
{
  // MISRA
}
