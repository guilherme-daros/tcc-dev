#include "server_functions.h"
#include "btstack.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"

#include <stdio.h>

namespace {} // namespace

// clang-format off
uint8_t adv_data[] = {
    0x02, BLUETOOTH_DATA_TYPE_FLAGS, 0x06,
    // Name
    0x0a, BLUETOOTH_DATA_TYPE_COMPLETE_LOCAL_NAME, 'P', 'i', 'c', 'o', 'W', '-', 'B', 'L', 'E', 
    0x03, BLUETOOTH_DATA_TYPE_COMPLETE_LIST_OF_16_BIT_SERVICE_CLASS_UUIDS, 0x1a, 0x18,
    0x09, BLUETOOTH_DATA_TYPE_SERVICE_DATA, 0x13,0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};
// clang-format on

uint8_t adv_data_len = sizeof(adv_data);

btstack_timer_source_t adv_temp_humi;
uint8_t acc_x = 0;
uint8_t acc_y = 0;
uint8_t acc_z = 0;

void adv_temp_humi_handler(struct btstack_timer_source *ts) {

  adv_data[23] = acc_x++;
  adv_data[25] = acc_y++;
  adv_data[27] = acc_z++;

  gap_advertisements_set_data(adv_data_len, adv_data);

  // btstack_run_loop_set_timer(ts, ADV_TEMP_HUMI_PERIOD_MS);
  // btstack_run_loop_add_timer(ts);
}

void ble_init_all(uint16_t adv_interval) {
  if (cyw43_arch_init()) {
    printf("cyw43_init error\n");
    return;
  }

  l2cap_init();
  sm_init();
  uint16_t adv_int_min = adv_interval;
  uint16_t adv_int_max = adv_interval;

  constexpr uint8_t adv_type = 2; // only advertisement, not connectable.
  bd_addr_t null_addr;

  memset(null_addr, 0, 6);
  gap_advertisements_set_params(adv_int_min, adv_int_max, adv_type, 0,
                                null_addr, 0x07, 0x00);
  gap_advertisements_set_data(adv_data_len, (uint8_t *)adv_data);
  gap_advertisements_enable(true);

  adv_temp_humi_handler(&adv_temp_humi);
}