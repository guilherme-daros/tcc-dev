#include "constants.h"
#include "model.h"
#include "output_handler.h"
#include "pico/stdlib.h"
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"
#include <iostream>

namespace {
tflite::ErrorReporter *error_reporter = nullptr;
const tflite::Model *model = nullptr;
tflite::MicroInterpreter *interpreter = nullptr;
int inference_count = 0;

constexpr int kTensorArenaSize = 1024 * 50;
uint8_t tensor_arena[kTensorArenaSize];
} // namespace

int main(int argc, char *argv[]) {
  stdio_init_all();
  sleep_ms(5000);
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

  model = tflite::GetModel(hello_world_models_hello_world_float_tflite);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    TF_LITE_REPORT_ERROR(error_reporter,
                         "Model provided is schema version %d not equal "
                         "to supported version %d.",
                         model->version(), TFLITE_SCHEMA_VERSION);
  }

  static tflite::AllOpsResolver resolver;

  static tflite::MicroInterpreter static_interpreter(
      model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
  interpreter = &static_interpreter;

  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "AllocateTensors() failed");
  }

  TF_LITE_REPORT_ERROR(error_reporter, "arena_used_bytes: %d",
                       interpreter->arena_used_bytes());

  auto t_inputs = interpreter->typed_input_tensor<float>(0);

  std::array<float, 15> test_input = {
      0.23963562, 0.41354273, 0.28585349,  0.23963562,  0.41354273,
      0.28585349, -0.4922426, -0.42818671, -0.58662862, 0.62113279,
      0.79802761, 0.71127406, -0.84421278, -0.88943599, -0.88671531};

  std::copy(test_input.begin(), test_input.end(),
            interpreter->typed_input_tensor<float>(0));

  TF_LITE_REPORT_ERROR(error_reporter, "input shape: (%d, %d)",
                       interpreter->input(0)->dims->data[0],

                       interpreter->input(0)->dims->data[1]);

  if (interpreter->Invoke() == kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "Invoke() succeded");
  } else {
    TF_LITE_REPORT_ERROR(error_reporter, "Invoke() failed");
  }
  auto output_index = interpreter->outputs()[0];
  const float *output_data = interpreter->typed_tensor<float>(output_index);

  // Post-process the output (depends on the model and task)
  // For image classification, you might want to find the top class label
  int top_class = 0;
  float max_score = output_data[0];
  for (int i = 1; i < interpreter->tensor(output_index)->dims->data[1]; i++) {
    if (output_data[i] > max_score) {
      max_score = output_data[i];
      top_class = i;
    }
    TF_LITE_REPORT_ERROR(error_reporter, "Class: %d got score %f", i,
                         output_data[i]);
  }

  TF_LITE_REPORT_ERROR(error_reporter, "Predicted Class %d", top_class);

  while (true) {
    tight_loop_contents();
  }
}
