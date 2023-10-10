#include "config.h"
#include "log.h"

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"

int main() {
  stdio_init_all();

  if (cyw43_arch_init()) {
    printf("Wi-Fi init failed");
    return -1;
  }

  TaskHandle_t printName1 = NULL;
  TaskHandle_t printName2 = NULL;
  TaskHandle_t printBlink = NULL;

  xTaskCreate(
      [](void *param) {
        while (true) {
          cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
          vTaskDelay(250);
          cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
          vTaskDelay(250);
        }
      },
      "Name Task", 1024, NULL, tskIDLE_PRIORITY, &printBlink);

  xTaskCreate(
      [](void *param) {
        while (true) {
          log::Log(config::name);
          vTaskDelay(1000);
        }
      },
      "Name Task", 1024, NULL, tskIDLE_PRIORITY, &printName1);

  xTaskCreate(
      [](void *param) {
        while (true) {
          log::Log("Guilherme");
          vTaskDelay(1000);
        }
      },
      "Age Task", 1024, NULL, tskIDLE_PRIORITY, &printName2);

  vTaskStartScheduler();
}