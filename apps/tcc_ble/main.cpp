#include "btstack.h"
#include "gatt_ht_server.h"
#include "log.h"
#include "math.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include "server_functions.h"
#include <stdio.h>

int main() {
  stdio_init_all();
  if (cyw43_arch_init()) {
    printf("cyw43_init error\n");
    return 0;
  }

  l2cap_init();
  sm_init();

  // setup advertisements
  uint16_t adv_int_min = 0x0030;
  uint16_t adv_int_max = 0x0030;
  uint8_t adv_type = 1;
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

  // set  timer
  temp_humi_noti.process = &temp_humi_handle;
  btstack_run_loop_set_timer(&temp_humi_noti, HEARTBEAT_PERIOD_MS);
  btstack_run_loop_add_timer(&temp_humi_noti);

  hci_power_control(HCI_POWER_ON);

  while (true) {
    tight_loop_contents();
  }

  return 0;
}