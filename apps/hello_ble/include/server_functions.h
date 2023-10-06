#pragma once

#include "btstack.h"
#include "gatt_ht_server.h"
#include "math.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include <stdio.h>

#define HEARTBEAT_PERIOD_MS 3000

extern uint8_t adv_data[];
extern uint8_t adv_data_len;
extern float temp;
extern float humi;
extern uint16_t temp_i, humi_i;
extern bool le_notification_enabled;
extern hci_con_handle_t con_handle;
extern btstack_packet_callback_registration_t hci_event_callback_registration;
extern btstack_timer_source_t temp_humi_noti;

uint16_t att_read_callback(hci_con_handle_t connection_handle,
                           uint16_t att_handle, uint16_t offset,
                           uint8_t *buffer, uint16_t buffer_size);

int att_write_callback(hci_con_handle_t connection_handle, uint16_t att_handle,
                       uint16_t transaction_mode, uint16_t offset,
                       uint8_t *buffer, uint16_t buffer_size);

void temp_humi_handle(struct btstack_timer_source *ts);

void packet_handler(uint8_t packet_type, uint16_t channel, uint8_t *packet,
                    uint16_t size);