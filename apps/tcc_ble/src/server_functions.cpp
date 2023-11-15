#include "server_functions.h"
#include "btstack.h"
#include "gatt_ht_server.h"
#include "log.h"
#include "math.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include <stdio.h>

// clang-format off
uint8_t adv_data[] = {
    0x02, BLUETOOTH_DATA_TYPE_FLAGS, 0x06,
    0x09, BLUETOOTH_DATA_TYPE_COMPLETE_LOCAL_NAME, 'P','i','c','o','W','-','H','T',
    0x03, BLUETOOTH_DATA_TYPE_INCOMPLETE_LIST_OF_16_BIT_SERVICE_CLASS_UUIDS, 0x1a, 0x18};
// clang-format on

uint8_t adv_data_len = sizeof(adv_data);

float temp;
float humi;
uint16_t temp_i, humi_i;
bool le_notification_enabled;
hci_con_handle_t con_handle;
btstack_packet_callback_registration_t hci_event_callback_registration;
btstack_timer_source_t temp_humi_noti;

uint16_t att_read_callback(hci_con_handle_t connection_handle,
                           uint16_t att_handle, uint16_t offset,
                           uint8_t *buffer, uint16_t buffer_size) {
  logger::Log("Read request received");
  if (att_handle ==
      ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_TEMPERATURE_01_VALUE_HANDLE) {
    att_server_request_can_send_now_event(connection_handle);
    return att_read_callback_handle_little_endian_16(temp_i, offset, buffer,
                                                     buffer_size);
  }
  if (att_handle ==
      ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_HUMIDITY_01_VALUE_HANDLE) {
    uint16_t ret = att_read_callback_handle_little_endian_16(
        humi_i, offset, buffer, buffer_size);
    att_server_request_can_send_now_event(connection_handle);
    return ret;
  }

  return 0;
}

int att_write_callback(hci_con_handle_t connection_handle, uint16_t att_handle,
                       uint16_t transaction_mode, uint16_t offset,
                       uint8_t *buffer, uint16_t buffer_size) {
  UNUSED(transaction_mode);
  UNUSED(offset);
  UNUSED(buffer_size);
  logger::Log("Write request received");
  if (att_handle ==
          ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_TEMPERATURE_01_CLIENT_CONFIGURATION_HANDLE ||
      att_handle ==
          ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_HUMIDITY_01_CLIENT_CONFIGURATION_HANDLE) {
    le_notification_enabled =
        little_endian_read_16(buffer, 0) ==
        GATT_CLIENT_CHARACTERISTICS_CONFIGURATION_NOTIFICATION;
    con_handle = connection_handle;
  }
  return 0;
}

void temp_humi_handle(struct btstack_timer_source *ts) {

  if (le_notification_enabled) {
    temp = 24.22;
    humi = 75;
    if (true) {
      temp_i = (uint16_t)round(temp * 100);
      humi_i = (uint16_t)round(humi * 100);
      logger::Log("Sending Enviromental data");
      att_server_request_can_send_now_event(con_handle);
    }
  }

  // Invert the led
  static int led_on = true;
  led_on = !led_on;
  logger::Log("Changing LED state");
  cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);

  btstack_run_loop_set_timer(ts, HEARTBEAT_PERIOD_MS);
  btstack_run_loop_add_timer(ts);
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
    att_server_notify(
        con_handle,
        ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_TEMPERATURE_01_VALUE_HANDLE,
        (uint8_t *)&temp_i, 2);
    att_server_notify(
        con_handle,
        ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_HUMIDITY_01_VALUE_HANDLE,
        (uint8_t *)&humi_i, 2);
    break;
  default:
    break;
  }
}