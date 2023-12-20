#pragma once

#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>

extern int addr;

extern i2c_inst_t *i2c;
extern const uint sda_pin;
extern const uint scl_pin;

void mpu6050_reset();

void mpu6050_read_raw(int16_t accel[3], int16_t gyro[3], int16_t *temp);