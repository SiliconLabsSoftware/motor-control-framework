/***************************************************************************//**
 * @file
 * @brief Top level application functions
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
#include "app.h"
#include "Arduino.h"
#include "motor_control.h"
#ifdef __cplusplus
extern "C" {
#include "sl_bt_api.h"
#include "motor_control_framework_config.h"
}
#endif
/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void)
{
  // Initialize Arduino variant
  arduino_layer_init();
  motor_control_init();
#if ENABLE_BLE
  sl_bt_system_start_bluetooth();
#endif
}

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void)
{
  // application runs in freeRTOS tasks, so we don't need to do anything here
}
