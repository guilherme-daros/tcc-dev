#include "server_functions.h"
#include "btstack.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"

#include <stdio.h>

// clang-format off
uint8_t adv_data[] = {
    // Flags: 0x02: General Discoverable Mode, 0x04:BR/EDR Not Supported
    0x02, BLUETOOTH_DATA_TYPE_FLAGS, 0x06,
    // Name
    0x0a, BLUETOOTH_DATA_TYPE_COMPLETE_LOCAL_NAME, 'P', 'i', 'c', 'o', 'W', '-', 'B', 'L', 'E', 
    0x03, BLUETOOTH_DATA_TYPE_COMPLETE_LIST_OF_16_BIT_SERVICE_CLASS_UUIDS, 0x1a, 0x18,
    //Temperature UUID:0x2A5E
    0x04, BLUETOOTH_DATA_TYPE_SERVICE_DATA, 0x6E,0x2A,0x00, 
    //Humidity UUID: 0x2A6F
    0x04, BLUETOOTH_DATA_TYPE_SERVICE_DATA, 0x6F,0x2A,0x00, 

};
// clang-format on

uint8_t adv_data_len = sizeof(adv_data);

btstack_timer_source_t adv_temp_humi;
uint8_t temp = 0;
uint8_t humi = 0;

void adv_temp_humi_handler(struct btstack_timer_source *ts) {

  adv_data[adv_data_len - 1] = temp++;
  adv_data[adv_data_len - 6] = humi++;

  gap_advertisements_set_data(adv_data_len, adv_data);

  // btstack_run_loop_set_timer(ts, ADV_TEMP_HUMI_PERIOD_MS);
  // btstack_run_loop_add_timer(ts);
}
