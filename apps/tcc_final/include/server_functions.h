#pragma once

#include "btstack.h"
#include "math.h"
#include "physical_activity_monitor.h"

#include "tensorflow/lite/micro/micro_interpreter.h"

#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include <stdio.h>

#define HEARTBEAT_PERIOD_MS 500

namespace {
constexpr int kTxFrequency = 1;       // max_value = 40
constexpr int kTxInterval = 1000 * 5; // 1 / kTxFrequency;
//  Minimum advertising interval for undirected
//  and low duty cycle directed advertising.
//  Range: 0x0020 to 0x4000
//  Time = N * 0.625 ms
//  Time Range: 20 ms to 10.24 sec
//  Set to minimum because we're controlling this stuff with delays
constexpr uint16_t adv_interval =
    0x0020 + static_cast<int>((kTxInterval - 20) / 0.625);
} // namespace

extern uint8_t adv_data[];
extern uint8_t adv_data_len;

extern float activity;
extern uint16_t activity_i;

extern bool le_notification_enabled;

extern hci_con_handle_t con_handle;
extern btstack_packet_callback_registration_t hci_event_callback_registration;
extern btstack_timer_source_t activity_summary_noti;

extern tflite::MicroInterpreter *interpreter;

uint16_t att_read_callback(hci_con_handle_t connection_handle,
                           uint16_t att_handle, uint16_t offset,
                           uint8_t *buffer, uint16_t buffer_size);

int att_write_callback(hci_con_handle_t connection_handle, uint16_t att_handle,
                       uint16_t transaction_mode, uint16_t offset,
                       uint8_t *buffer, uint16_t buffer_size);

void activity_summary_handle(struct btstack_timer_source *ts);

void packet_handler(uint8_t packet_type, uint16_t channel, uint8_t *packet,
                    uint16_t size);

void init_ble_service();