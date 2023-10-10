#include "config.h"
#include "log.h"

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

#include "pico/stdlib.h"

int main() {
  stdio_init_all();

  TaskHandle_t printName = NULL;
  TaskHandle_t printAge = NULL;

  xTaskCreate(
      [](void *param) {
        while (true) {
          log::Log(config::name);
          vTaskDelay(1000);
        }
      },
      "Name Task", 1024, NULL, tskIDLE_PRIORITY, &printName);

  xTaskCreate(
      [](void *param) {
        while (true) {
          log::Log("Guilherme");
          vTaskDelay(1000);
        }
      },
      "Age Task", 1024, NULL, tskIDLE_PRIORITY, &printAge);

  vTaskStartScheduler();
}