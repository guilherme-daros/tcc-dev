#include "data_54.h"
#include "feature_extraction.h"
#include "model2.h"

#include "pico/runtime.h"
#include "pico/stdlib.h"
#include "pico/time.h"

#include "btstack.h"
#include "pico/cyw43_arch.h"
#include "server_functions.h"

#include <array>
#include <chrono>
#include <iostream>

int main() {
  stdio_init_all();
  sleep_ms(3000);

  if (cyw43_arch_init()) {
    printf("cyw43_init error\n");
  }

  l2cap_init();
  sm_init();
  constexpr uint16_t adv_int_min = 0x20;
  constexpr uint16_t adv_int_max = 0x20;

  constexpr uint8_t adv_type = 2; // only advertisement, not connectable.
  bd_addr_t null_addr;

  memset(null_addr, 0, 6);
  gap_advertisements_set_params(adv_int_min, adv_int_max, adv_type, 0,
                                null_addr, 0x07, 0x00);
  gap_advertisements_set_data(adv_data_len, (uint8_t *)adv_data);
  gap_advertisements_enable(true);

  adv_temp_humi.process = &adv_temp_humi_handler;
  btstack_run_loop_set_timer(&adv_temp_humi, ADV_TEMP_HUMI_PERIOD_MS);
  btstack_run_loop_add_timer(&adv_temp_humi);

  hci_power_control(HCI_POWER_ON);

  while (true)
    tight_loop_contents();
  return 0;
}