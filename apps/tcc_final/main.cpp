#include "data_432.h"
#include "feature_extraction.h"
#include "model2.h"

#include "logger.h"
#include "pico/runtime.h"
#include "pico/stdlib.h"

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

} // namespace

int main(int argc, char *argv[]) {
  stdio_init_all();
  sleep_ms(5000);
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

  model = tflite::GetModel(lw64_md8);
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

  // std::cout << "arena_used_bytes: " << interpreter->arena_used_bytes()
  //           << std::endl;

  static data_window<int, 432> dw;
  static int read_count = 0;

  while (true) {
    if (!dw.is_ready()) {

      auto [x, y, z] = vec432[read_count];
      dw.add(x, y, z);
      read_count++;

    } else {

      auto start = time_us_64();
      auto data = get_features<int, 432>(dw);
      std::cout << "Took " << time_us_64() - start << " us to get_features"
                << std::endl;

      start = time_us_64();
      std::copy(data.begin(), data.end(),
                interpreter->typed_input_tensor<float>(0));
      std::cout << "Took " << time_us_64() - start << " us to copy data"
                << std::endl;

      start = time_us_64();
      interpreter->Invoke();
      std::cout << "Took " << time_us_64() - start << " us to run model"
                << std::endl;

      dw.reset();
      sleep_ms(10000);
    }
  }
}
