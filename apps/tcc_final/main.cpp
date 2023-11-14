#include "data_108.h"
#include "feature_extraction.h"
#include "model2.h"

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
      ? std::cout << "AllocateTensors() succeded" << std::endl
      : std::cout << "AllocateTensors() failed" << std::endl;

  // std::cout << "arena_used_bytes: " << interpreter->arena_used_bytes()
  //           << std::endl;

  static data_window<int, 108> dw;
  static int read_count = 0;

  while (true) {
    if (!dw.is_ready()) {

      auto [x, y, z] = vec108[read_count];
      dw.add(x, y, z);
      read_count++;

    } else {

      auto data = get_features<int, 108>(dw);

      std::copy(data.begin(), data.end(),
                interpreter->typed_input_tensor<float>(0));
      auto start = std::chrono::system_clock::now();
      interpreter->Invoke() == kTfLiteOk
          ? std::cout << "Invoke() succeded" << std::endl
          : std::cout << "Invoke() failed" << std::endl;
      auto end = std::chrono::system_clock::now();
      std::cout << "Invoke duration: "
                << std::chrono::duration_cast<std::chrono::seconds>(end - start)
                       .count()
                << std::endl;
      const float *output_data = interpreter->typed_output_tensor<float>(0);
    }
  }
}
