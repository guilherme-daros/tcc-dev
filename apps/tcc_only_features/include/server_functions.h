#pragma once

#include "btstack.h"
#include "math.h"

#include "tensorflow/lite/micro/micro_interpreter.h"

#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include <stdio.h>

#define ADV_TEMP_HUMI_PERIOD_MS 3000

extern uint8_t adv_data[];
extern uint8_t adv_data_len;

extern btstack_timer_source_t adv_temp_humi;
extern uint8_t acc_x;
extern uint8_t acc_y;
extern uint8_t acc_z;

void adv_temp_humi_handler(struct btstack_timer_source *ts);

void ble_init_all();