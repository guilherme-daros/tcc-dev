
// gatt_ht_server.h generated from gatt_ht_server.gatt for BTstack
// it needs to be regenerated when the .gatt file is updated.

// To generate gatt_ht_server.h:
// /home/ghd/Documents/pico-sdk/lib/btstack/tool/compile_gatt.py
// gatt_ht_server.gatt gatt_ht_server.h

// att db format version 1

// binary attribute representation:
// - size in bytes (16), flags(16), handle (16), uuid (16/128), value(...)
#pragma once

#include <stdint.h>

constexpr const uint8_t profile_data[] = {
    // ATT DB Version
    1,

    // 0x0001 PRIMARY_SERVICE-GAP_SERVICE
    0x0a,
    0x00,
    0x02,
    0x00,
    0x01,
    0x00,
    0x00,
    0x28,
    0x00,
    0x18,
    // 0x0002 CHARACTERISTIC-GAP_DEVICE_NAME - READ
    0x0d,
    0x00,
    0x02,
    0x00,
    0x02,
    0x00,
    0x03,
    0x28,
    0x02,
    0x03,
    0x00,
    0x00,
    0x2a,
    // 0x0003 VALUE CHARACTERISTIC-GAP_DEVICE_NAME - READ -'tcc-test'
    // READ_ANYBODY
    0x10,
    0x00,
    0x02,
    0x00,
    0x03,
    0x00,
    0x00,
    0x2a,
    0x74,
    0x63,
    0x63,
    0x2d,
    0x74,
    0x65,
    0x73,
    0x74,
    // 0x0004 PRIMARY_SERVICE-GATT_SERVICE
    0x0a,
    0x00,
    0x02,
    0x00,
    0x04,
    0x00,
    0x00,
    0x28,
    0x01,
    0x18,
    // 0x0005 CHARACTERISTIC-GATT_DATABASE_HASH - READ
    0x0d,
    0x00,
    0x02,
    0x00,
    0x05,
    0x00,
    0x03,
    0x28,
    0x02,
    0x06,
    0x00,
    0x2a,
    0x2b,
    // 0x0006 VALUE CHARACTERISTIC-GATT_DATABASE_HASH - READ -''
    // READ_ANYBODY
    0x18,
    0x00,
    0x02,
    0x00,
    0x06,
    0x00,
    0x2a,
    0x2b,
    0xcd,
    0xf2,
    0x83,
    0x5b,
    0x3c,
    0x18,
    0x84,
    0x0e,
    0xa6,
    0xc5,
    0x34,
    0x6e,
    0x4a,
    0xd4,
    0xe1,
    0x30,
    // Environment
    // 0x0007 PRIMARY_SERVICE-ORG_BLUETOOTH_SERVICE_ENVIRONMENTAL_SENSING
    0x0a,
    0x00,
    0x02,
    0x00,
    0x07,
    0x00,
    0x00,
    0x28,
    0x1a,
    0x18,
    // Temperature Characteristic, with read and notify
    // 0x0008 CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_TEMPERATURE - READ
    // | NOTIFY | DYNAMIC
    0x0d,
    0x00,
    0x02,
    0x00,
    0x08,
    0x00,
    0x03,
    0x28,
    0x12,
    0x09,
    0x00,
    0x6e,
    0x2a,
    // 0x0009 VALUE CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_TEMPERATURE
    // - READ | NOTIFY | DYNAMIC READ_ANYBODY
    0x08,
    0x00,
    0x02,
    0x01,
    0x09,
    0x00,
    0x6e,
    0x2a,
    // 0x000a CLIENT_CHARACTERISTIC_CONFIGURATION
    // READ_ANYBODY, WRITE_ANYBODY
    0x0a,
    0x00,
    0x0e,
    0x01,
    0x0a,
    0x00,
    0x02,
    0x29,
    0x00,
    0x00,
    // Humidity Characteristic, with read and notify
    // 0x000b CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_HUMIDITY - READ |
    // NOTIFY | DYNAMIC
    0x0d,
    0x00,
    0x02,
    0x00,
    0x0b,
    0x00,
    0x03,
    0x28,
    0x12,
    0x0c,
    0x00,
    0x6f,
    0x2a,
    // 0x000c VALUE CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_HUMIDITY -
    // READ | NOTIFY | DYNAMIC READ_ANYBODY
    0x08,
    0x00,
    0x02,
    0x01,
    0x0c,
    0x00,
    0x6f,
    0x2a,
    // 0x000d CLIENT_CHARACTERISTIC_CONFIGURATION
    // READ_ANYBODY, WRITE_ANYBODY
    0x0a,
    0x00,
    0x0e,
    0x01,
    0x0d,
    0x00,
    0x02,
    0x29,
    0x00,
    0x00,
    // END
    0x00,
    0x00,
}; // total size 84 bytes

//
// list service handle ranges
//
#define ATT_SERVICE_GAP_SERVICE_START_HANDLE 0x0001
#define ATT_SERVICE_GAP_SERVICE_END_HANDLE 0x0003
#define ATT_SERVICE_GAP_SERVICE_01_START_HANDLE 0x0001
#define ATT_SERVICE_GAP_SERVICE_01_END_HANDLE 0x0003
#define ATT_SERVICE_GATT_SERVICE_START_HANDLE 0x0004
#define ATT_SERVICE_GATT_SERVICE_END_HANDLE 0x0006
#define ATT_SERVICE_GATT_SERVICE_01_START_HANDLE 0x0004
#define ATT_SERVICE_GATT_SERVICE_01_END_HANDLE 0x0006
#define ATT_SERVICE_ORG_BLUETOOTH_SERVICE_ENVIRONMENTAL_SENSING_START_HANDLE   \
  0x0007
#define ATT_SERVICE_ORG_BLUETOOTH_SERVICE_ENVIRONMENTAL_SENSING_END_HANDLE     \
  0x000d
#define ATT_SERVICE_ORG_BLUETOOTH_SERVICE_ENVIRONMENTAL_SENSING_01_START_HANDLE \
  0x0007
#define ATT_SERVICE_ORG_BLUETOOTH_SERVICE_ENVIRONMENTAL_SENSING_01_END_HANDLE  \
  0x000d

//
// list mapping between characteristics and handles
//
#define ATT_CHARACTERISTIC_GAP_DEVICE_NAME_01_VALUE_HANDLE 0x0003
#define ATT_CHARACTERISTIC_GATT_DATABASE_HASH_01_VALUE_HANDLE 0x0006
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_TEMPERATURE_01_VALUE_HANDLE \
  0x0009
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_TEMPERATURE_01_CLIENT_CONFIGURATION_HANDLE \
  0x000a
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_HUMIDITY_01_VALUE_HANDLE \
  0x000c
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_HUMIDITY_01_CLIENT_CONFIGURATION_HANDLE \
  0x000d
