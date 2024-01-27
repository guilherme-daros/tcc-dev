#include "server_functions.h"
#include "btstack.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"

#include <stdio.h>

namespace {
//  Minimum advertising interval for undirected
//  and low duty cycle directed advertising.
//  Range: 0x0020 to 0x4000
//  Time = N * 0.625 ms
//  Time Range: 20 ms to 10.24 sec
//  Set to minimum because we're controlling this stuff with delays
constexpr uint16_t adv_interval = 0x0020;
} // namespace

// clang-format off
uint8_t adv_data[] = {
    0x02, BLUETOOTH_DATA_TYPE_FLAGS, 0x06,
    // Name
    0x0a, BLUETOOTH_DATA_TYPE_COMPLETE_LOCAL_NAME, 'P', 'i', 'c', 'o', 'W', '-', 'B', 'L', 'E', 
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

  btstack_run_loop_set_timer(ts, ADV_TEMP_HUMI_PERIOD_MS);
  btstack_run_loop_add_timer(ts);
}