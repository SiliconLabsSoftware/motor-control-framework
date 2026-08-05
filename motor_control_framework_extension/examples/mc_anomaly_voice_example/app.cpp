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
#include "imu_task.h"
#include "audio_classifier.h"
#include "blinky.h"
#include "sl_bt_api.h"
#include "telemetry.h"
#include "sl_simple_button_instances.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#ifndef MODEL_SWITCH_TASK_STACK_SIZE
#define MODEL_SWITCH_TASK_STACK_SIZE      256
#endif

#ifndef MODEL_SWITCH_TASK_PRIO
#define MODEL_SWITCH_TASK_PRIO            35
#endif

static app_model_t active_model = APP_MODEL_NONE;
static uint32_t last_button_press_time = 0;
static const uint32_t DEBOUNCE_DELAY_MS = 500;
static TaskHandle_t xModelSwitchTaskHandle = NULL;
static QueueHandle_t xModelSwitchQueue = NULL;
static volatile bool model_switch_in_progress = false;

app_model_t app_get_active_model(void)
{
  return active_model;
}

static void model_switch_task(void *arg)
{
  (void)arg;
  app_model_t requested_model;

  while (1) {
    if (xQueueReceive(xModelSwitchQueue, &requested_model, portMAX_DELAY) == pdTRUE) {
      if (active_model != requested_model && !model_switch_in_progress) {
        model_switch_in_progress = true;

        Serial.print("Switching from model ");
        Serial.print(active_model);
        Serial.print(" to model ");
        Serial.println(requested_model);

        if (active_model == APP_MODEL_AUDIO) {
          audio_classifier_deinit();
        } else if (active_model == APP_MODEL_IMU) {
          imu_task_deinit();
        }

        vTaskDelay(pdMS_TO_TICKS(100));

        active_model = requested_model;

        if (requested_model == APP_MODEL_AUDIO) {
          audio_classifier_init();
        } else if (requested_model == APP_MODEL_IMU) {
          imu_task_init();
        }

        Serial.println("Model switch complete");
        model_switch_in_progress = false;
      }
    }
  }
}

void app_select_model(app_model_t model)
{
  if (active_model == model) {
    return;
  }

  if (active_model == APP_MODEL_AUDIO) {
    audio_classifier_deinit();
  } else if (active_model == APP_MODEL_IMU) {
    imu_task_deinit();
  }

  active_model = model;

  if (model == APP_MODEL_AUDIO) {
    audio_classifier_init();
  } else if (model == APP_MODEL_IMU) {
    imu_task_init();
  }
}

void app_request_model_switch(app_model_t model)
{
  BaseType_t woken = pdFALSE;

  if (xModelSwitchQueue != NULL && !model_switch_in_progress) {
    if (xPortIsInsideInterrupt()) {
      xQueueSendFromISR(xModelSwitchQueue, &model, &woken);
      portYIELD_FROM_ISR(woken);
    } else {
      xQueueSend(xModelSwitchQueue, &model, 0);
    }
  }
}
/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void)
{
  static StaticTask_t xTaskBuffer;
  static StackType_t  xStack[MODEL_SWITCH_TASK_STACK_SIZE];
  static StaticQueue_t xQueueBuffer;
  static uint8_t ucQueueStorage[5 * sizeof(app_model_t)];

  // Initialize Arduino variant
  arduino_layer_init();
  motor_control_init();

  xModelSwitchQueue = xQueueCreateStatic(5,
                                         sizeof(app_model_t),
                                         ucQueueStorage,
                                         &xQueueBuffer);
  EFM_ASSERT(xModelSwitchQueue != NULL);

  xModelSwitchTaskHandle = xTaskCreateStatic(model_switch_task,
                                             "model switch task",
                                             MODEL_SWITCH_TASK_STACK_SIZE,
                                             (void *)NULL,
                                             MODEL_SWITCH_TASK_PRIO,
                                             xStack,
                                             &xTaskBuffer);
  EFM_ASSERT(xModelSwitchTaskHandle != NULL);

  app_select_model(APP_MODEL_IMU);
  blinky_init();
  sl_bt_system_start_bluetooth();
  telemetry_init();
}

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void)
{
}

void sl_button_on_change(const sl_button_t *handle)
{
  if (sl_button_get_state(handle) == SL_SIMPLE_BUTTON_PRESSED) {
    uint32_t current_time = millis();
    if (current_time - last_button_press_time >= DEBOUNCE_DELAY_MS) {
      last_button_press_time = current_time;
      app_model_t next_model;
      if (active_model == APP_MODEL_AUDIO) {
        next_model = APP_MODEL_IMU;
      } else {
        next_model = APP_MODEL_AUDIO;
      }
      app_request_model_switch(next_model);
    }
  }
}
