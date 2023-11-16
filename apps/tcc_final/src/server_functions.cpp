#include "server_functions.h"
#include "btstack.h"
#include "log.h"
#include "math.h"
#include "physical_activity_monitor.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include <stdio.h>

// clang-format off
uint8_t adv_data[] = {
    0x02, BLUETOOTH_DATA_TYPE_FLAGS, 0x06,
    0x0A, BLUETOOTH_DATA_TYPE_COMPLETE_LOCAL_NAME, 'P','i','c','o','W','-','B', 'L', 'E'
    };
// clang-format on

uint8_t adv_data_len = sizeof(adv_data);

float activity;
uint16_t activity_i;

bool le_notification_enabled;
hci_con_handle_t con_handle;

uint64_t last_notify;

btstack_packet_callback_registration_t hci_event_callback_registration;
btstack_timer_source_t activity_summary_noti;

uint16_t att_read_callback(hci_con_handle_t connection_handle,
                           uint16_t att_handle, uint16_t offset,
                           uint8_t *buffer, uint16_t buffer_size) {
  logger::Log("Read request received");
  if (att_handle ==
      ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_GENERAL_ACTIVITY_SUMMARY_DATA_01_VALUE_HANDLE) {
    att_server_request_can_send_now_event(connection_handle);
    return att_read_callback_handle_little_endian_16(activity_i, offset, buffer,
                                                     buffer_size);
  }
  return 0;
}

int att_write_callback(hci_con_handle_t connection_handle, uint16_t att_handle,
                       uint16_t transaction_mode, uint16_t offset,
                       uint8_t *buffer, uint16_t buffer_size) {

  UNUSED(transaction_mode);
  UNUSED(offset);
  UNUSED(buffer_size);

  if (att_handle ==
      ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_GENERAL_ACTIVITY_SUMMARY_DATA_01_CLIENT_CONFIGURATION_HANDLE) {

    le_notification_enabled =
        little_endian_read_16(buffer, 0) ==
        GATT_CLIENT_CHARACTERISTICS_CONFIGURATION_NOTIFICATION;

    le_notification_enabled ? logger::Log("Enable Notifications")
                            : logger::Log("Disable Notifications");

    con_handle = connection_handle;
  }
  return 0;
}

void activity_summary_handle(struct btstack_timer_source *ts) {

  // Notify if enable
  if (le_notification_enabled) {
    activity = 0;
    activity_i = (uint16_t)round(activity);
    att_server_request_can_send_now_event(con_handle);
  }
}

void packet_handler(uint8_t packet_type, uint16_t channel, uint8_t *packet,
                    uint16_t size) {

  UNUSED(channel);
  UNUSED(size);

  if (packet_type != HCI_EVENT_PACKET)
    return;
  switch (hci_event_packet_get_type(packet)) {
  case HCI_EVENT_DISCONNECTION_COMPLETE:
    le_notification_enabled = 0;
    logger::Log("Device Disconnected");
    break;
  case ATT_EVENT_CAN_SEND_NOW:
    logger::Log("Sending Activity data");
    att_server_notify(
        con_handle,
        ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_GENERAL_ACTIVITY_SUMMARY_DATA_01_VALUE_HANDLE,
        (uint8_t *)&activity_i, 2);
    break;
  default:
    break;
  }
}

void init_ble_service() {
  if (cyw43_arch_init()) {
    printf("cyw43_init error\n");
    return;
  }

  l2cap_init();
  sm_init();

  // setup advertisements
  uint16_t adv_int_min = 0x0030;
  uint16_t adv_int_max = 0x0030;
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

  // set  timer
  // activity_summary_noti.process = &activity_summary_handle;
  // btstack_run_loop_set_timer(&activity_summary_noti, HEARTBEAT_PERIOD_MS);
  // btstack_run_loop_add_timer(&activity_summary_noti);

  hci_power_control(HCI_POWER_ON);
}