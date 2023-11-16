#include "data_54.h"
#include "feature_extraction.h"
#include "model2.h"
#include "server_functions.h"

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

#include "logger.h"

#include "pico/runtime.h"
#include "pico/stdlib.h"
#include "pico/time.h"

#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"

#include <array>
#include <chrono>
#include <iostream>

namespace {
tflite::ErrorReporter *error_reporter = nullptr;
tflite::MicroInterpreter *interpreter = nullptr;
const tflite::Model *model = nullptr;

constexpr int kTensorArenaSize = 1024 * 50;
uint8_t tensor_arena[kTensorArenaSize];

constexpr int kBufferSize = 100;
char buf[kBufferSize];

TaskHandle_t tflite_task = NULL;
TaskHandle_t blink_led_task = NULL;

} // namespace

int main(int argc, char *argv[]) {
  stdio_init_all();
  sleep_ms(2000);

  init_ble_service();

  xTaskCreate(
      [](void *param) {
        static tflite::MicroErrorReporter micro_error_reporter;
        error_reporter = &micro_error_reporter;

        model = tflite::GetModel(lw64_md8);
        if (model->version() != TFLITE_SCHEMA_VERSION) {
          std::cout << "Model provided is schema version " << model->version()
                    << " not equal to supported version"
                    << TFLITE_SCHEMA_VERSION << std::endl;
        }

        static tflite::AllOpsResolver resolver;

        static tflite::MicroInterpreter static_interpreter(
            model, resolver, tensor_arena, kTensorArenaSize, error_reporter);

        interpreter = &static_interpreter;

        interpreter->AllocateTensors() == kTfLiteOk
            ? logger::Log("AllocateTensors() succeded")
            : logger::Log("AllocateTensors() failed");

        sprintf(buf, "arena_used_bytes %d ", interpreter->arena_used_bytes());
        logger::Log(buf);
        memset(buf, 0, kBufferSize);

        static data_window<int, 54> dw;
        static int read_count = 0;

        while (true) {
          if (!dw.is_ready()) {

            auto [x, y, z] = vec54[read_count];
            dw.add(x, y, z);
            read_count++;

          } else {

            logger::Log("Finished reading data");

            auto start = time_us_64();

            auto data = get_features<int, 54>(dw);
            sprintf(buf, "Took %d us to get_features", time_us_64() - start);
            logger::Log(buf);
            memset(buf, 0, kBufferSize);

            start = time_us_64();
            std::copy(data.begin(), data.end(),
                      interpreter->typed_input_tensor<float>(0));
            sprintf(buf, "Took %d us to copy data", time_us_64() - start);
            logger::Log(buf);
            memset(buf, 0, kBufferSize);

            start = time_us_64();
            interpreter->Invoke();
            sprintf(buf, "Took %d us to run model", time_us_64() - start);
            logger::Log(buf);
            memset(buf, 0, kBufferSize);

            dw.reset();
            read_count = 0;
            vTaskDelay(10000);
          }
        }
      },
      "TFLite Task", 1024, NULL, 1, &tflite_task);

  xTaskCreate(
      [](void *param) {
        while (true) {
          activity_summary_handle(&activity_summary_noti);
          vTaskDelay(10000);
        }
      },
      "BLE Task", 1024, NULL, 2, &blink_led_task);

  xTaskCreate(
      [](void *param) {
        int led_on = true;
        while (true) {
          led_on = !led_on;
          cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
          vTaskDelay(1000);
        }
      },
      "Blink Led Task", 1024, NULL, tskIDLE_PRIORITY, &blink_led_task);

  vTaskStartScheduler();
}
