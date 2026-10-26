#include <stdio.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "ble_stream_adapter.h"
#include "motor_control.h"
#include "imu_task.h"
#include "app.h"

// Task to send data periodically to the web interface
static void telemetry_task(void *pvParameters)
{
  //wait for motor start
  vTaskDelay(pdMS_TO_TICKS(5000));
  while (motor_p == NULL) {
    printf("Telemetry waitig for motor Init, motor init failed?");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
  while (1) {
    //*********/
    // Collect data //
    // Motor parameters //
    float current_speed = motor_p->shaft_velocity;      // in rad/sec
    // Anomaly data //
    float anomaly = getAnomaly() * 100.0f;

    const char *model_str = app_get_active_model() == APP_MODEL_AUDIO ? "audio" : "imu";

    const char *status_str;
    if (current_speed > 0.5) {      // Threshold for "Running"
      status_str = "Running";
    } else {
      status_str = "Stop";
      anomaly = 0;
    }

    //Assembly message
    char feedback[60];
    snprintf(feedback, sizeof(feedback),
             "Motor: %s  Speed: %0.2f Anomaly: %.0f%% mode: %s\n",
             status_str, current_speed, anomaly, model_str);

    bleStreamAdapter.write((uint8_t *)feedback, strlen(feedback));

    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void telemetry_init(void)
{
  xTaskCreate(telemetry_task, "Telemetry_Task", 1024, NULL, 1, NULL);
}
