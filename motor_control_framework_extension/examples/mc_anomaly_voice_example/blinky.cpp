#include "sl_gpio.h"
#include "sl_hal_gpio.h"
// FreeRTOS headers are not covered by the provided Silicon Labs docs
#include "FreeRTOS.h"
#include "task.h"
#include "SEGGER_RTT.h"
#include "app.h"

// Configure PA07 as push-pull output and toggle it every 500 ms
static void pa07_toggle_task(void *pvParameters)
{
  // Define GPIO pin: Port A (0), Pin 7
  sl_gpio_t pa07_pin = {
    .port = 0,  // Port A
    .pin  = 7   // Pin 7
  };

  // Configure PA07 as push-pull output, initial low
  sl_hal_gpio_set_pin_mode(&pa07_pin, SL_GPIO_MODE_PUSH_PULL, false);
  // (Pattern taken from the generic GPIO HAL example) [[xG23 GPIO HAL](https://docs.silabs.com/gecko-platform/latest/platform-peripheral-efr32xg23/gpio)]

  for (;; ) {
    // Toggle PA07
    sl_hal_gpio_toggle_pin(&pa07_pin);  // Same API as in the example [[xG23 GPIO HAL](https://docs.silabs.com/gecko-platform/latest/platform-peripheral-efr32xg23/gpio)]

    if (app_get_active_model() == APP_MODEL_AUDIO) {
      vTaskDelay(pdMS_TO_TICKS(1000));
    } else if (app_get_active_model() == APP_MODEL_IMU) {
      vTaskDelay(pdMS_TO_TICKS(300));
    } else {
      vTaskDelay(pdMS_TO_TICKS(100));
    }

    SEGGER_SYSVIEW_Print("SYSVIEW alive");
  }
}

void blinky_init(void)
{
  xTaskCreate(pa07_toggle_task, "PA07_Toggle", 128, NULL, 1, NULL);
}
