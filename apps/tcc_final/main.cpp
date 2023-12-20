#include "pico/runtime.h"
#include "pico/stdlib.h"
#include "pico/time.h"

#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"

#include "logger.h"
#include "model2.h"
#include "server_functions.h"

tflite::ErrorReporter *error_reporter = nullptr;
tflite::MicroInterpreter *interpreter = nullptr;
const tflite::Model *model = nullptr;

constexpr int kTensorArenaSize = 1024 * 50;
uint8_t tensor_arena[kTensorArenaSize];

constexpr int kBufferSize = 100;
char buf[kBufferSize];

int main(int argc, char *argv[]) {
  stdio_init_all();
  sleep_ms(2000);

  if (cyw43_arch_init()) {
    printf("cyw43_init error\n");
    return -1;
  }

  l2cap_init();
  sm_init();

  // setup advertisements
  uint16_t adv_int_min = adv_interval;
  uint16_t adv_int_max = adv_interval;
  uint8_t adv_type = 0;
  bd_addr_t null_addr;
  memset(null_addr, 0, 6);

  gap_advertisements_set_params(adv_int_min, adv_int_max, adv_type, 0,
                                null_addr, 0, 0x00);
  gap_advertisements_set_data(adv_data_len, (uint8_t *)adv_data);
  gap_advertisements_enable(1);

  // setup ATT server
  att_server_init(profile_data, att_read_callback, att_write_callback);

  // register for HCI events
  hci_event_callback_registration.callback = &packet_handler;
  hci_add_event_handler(&hci_event_callback_registration);

  // register for ATT event
  att_server_register_packet_handler(packet_handler);

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

  sprintf(buf, "arena_used_bytes %d ", interpreter->arena_used_bytes());
  logger::Log(buf);
  memset(buf, 0, kBufferSize);

  // set  timer
  activity_summary_noti.process = &activity_summary_handle;
  btstack_run_loop_set_timer(&activity_summary_noti, kTxInterval);
  btstack_run_loop_add_timer(&activity_summary_noti);

  logger::Log("Turning power on");
  hci_power_control(HCI_POWER_ON);

  while (true) {
    tight_loop_contents();
  }
}
