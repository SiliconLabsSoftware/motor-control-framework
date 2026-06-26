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

#ifndef APP_H
#define APP_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  APP_MODEL_NONE = -1,
  APP_MODEL_AUDIO = 0,
  APP_MODEL_IMU = 1
} app_model_t;

/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void);

void app_select_model(app_model_t model);

app_model_t app_get_active_model(void);

void app_request_model_switch(app_model_t model);

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void);

#ifdef __cplusplus
}
#endif

#endif  // APP_H
