#include "data_54.h"
#include "feature_extraction.h"
#include "model2.h"

#include "pico/runtime.h"
#include "pico/stdlib.h"
#include "pico/time.h"

#include "btstack.h"
#include "pico/cyw43_arch.h"
#include "server_functions.h"

#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"

#include <array>
#include <chrono>
#include <iostream>

namespace {
// TensorFlow stuff
tflite::ErrorReporter *error_reporter = nullptr;
tflite::MicroInterpreter *interpreter = nullptr;
const tflite::Model *model = nullptr;
constexpr int kTensorArenaSize = 1024 * 50;
uint8_t tensor_arena[kTensorArenaSize];

// Logging stuff
constexpr int kBufferSize = 100;
char buf[kBufferSize];
} // namespace

int main() {
  stdio_init_all();
  sleep_ms(3000);

  ble_init_all();

  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

  model = tflite::GetModel(lw4_md1);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    std::cout << "Model provided is schema version " << model->version()
              << " not equal to supported version" << TFLITE_SCHEMA_VERSION
              << std::endl;
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

  data_window<int, 54> dw;
  int read_count = 0;
  int run_count = 0;
  while (run_count <= 32) {
    if (!dw.is_ready()) {

      auto [x, y, z] = vec54[read_count];
      dw.add(x, y, z);
      read_count++;

    } else {

      // logger::Log("Finished reading data");

      auto start = time_us_64();
      auto data = get_features<int, 54>(dw);
      sprintf(buf, "%d \t", time_us_64() - start);
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

      // hci_power_control(HCI_POWER_ON);
      dw.reset();
      read_count = 0;
      sleep_ms(100);
      run_count++;
    }
  }
  while (true)
    tight_loop_contents();
  return 0;
}