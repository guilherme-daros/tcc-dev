
// ./apps/tcc_ble/include/physical_activity_monitor.h generated from ./apps/tcc_ble/include/physical_activity_monitor.gatt for BTstack
// it needs to be regenerated when the .gatt file is updated. 

// To generate ./apps/tcc_ble/include/physical_activity_monitor.h:
// ./lib/pico-sdk/lib/btstack/tool/compile_gatt.py ./apps/tcc_ble/include/physical_activity_monitor.gatt ./apps/tcc_ble/include/physical_activity_monitor.h

// att db format version 1

// binary attribute representation:
// - size in bytes (16), flags(16), handle (16), uuid (16/128), value(...)
#pragma once
#include <stdint.h>

// Reference: https://en.cppreference.com/w/cpp/feature_test
#if __cplusplus >= 200704L
constexpr
#endif
const uint8_t profile_data[] =
{
    // ATT DB Version
    1,

    // 0x0001 PRIMARY_SERVICE-GAP_SERVICE
    0x0a, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x28, 0x00, 0x18, 
    // 0x0002 CHARACTERISTIC-GAP_DEVICE_NAME - READ
    0x0d, 0x00, 0x02, 0x00, 0x02, 0x00, 0x03, 0x28, 0x02, 0x03, 0x00, 0x00, 0x2a, 
    // 0x0003 VALUE CHARACTERISTIC-GAP_DEVICE_NAME - READ -'tcc_ble'
    // READ_ANYBODY
    0x0f, 0x00, 0x02, 0x00, 0x03, 0x00, 0x00, 0x2a, 0x74, 0x63, 0x63, 0x5f, 0x62, 0x6c, 0x65, 
    // 0x0004 PRIMARY_SERVICE-GATT_SERVICE
    0x0a, 0x00, 0x02, 0x00, 0x04, 0x00, 0x00, 0x28, 0x01, 0x18, 
    // 0x0005 CHARACTERISTIC-GATT_DATABASE_HASH - READ
    0x0d, 0x00, 0x02, 0x00, 0x05, 0x00, 0x03, 0x28, 0x02, 0x06, 0x00, 0x2a, 0x2b, 
    // 0x0006 VALUE CHARACTERISTIC-GATT_DATABASE_HASH - READ -'NOTIFY'
    // READ_ANYBODY
    0x18, 0x00, 0x02, 0x00, 0x06, 0x00, 0x2a, 0x2b, 0xa1, 0x54, 0x61, 0x7b, 0xaa, 0x9e, 0x02, 0x8d, 0x51, 0x09, 0x13, 0xd6, 0xdf, 0x23, 0xfb, 0xec, 
    // Physical Activity
    // 0x0007 PRIMARY_SERVICE-ORG_BLUETOOTH_SERVICE_PHYSICAL_ACTIVITY_MONITOR
    0x0a, 0x00, 0x02, 0x00, 0x07, 0x00, 0x00, 0x28, 0x3e, 0x18, 
    // General Activity Characteristic, with read and notify
    // 0x0008 CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_GENERAL_ACTIVITY_SUMMARY_DATA - READ | NOTIFY | DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x08, 0x00, 0x03, 0x28, 0x12, 0x09, 0x00, 0x3d, 0x2b, 
    // 0x0009 VALUE CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_GENERAL_ACTIVITY_SUMMARY_DATA - READ | NOTIFY | DYNAMIC
    // READ_ANYBODY
    0x08, 0x00, 0x02, 0x01, 0x09, 0x00, 0x3d, 0x2b, 
    // 0x000a CLIENT_CHARACTERISTIC_CONFIGURATION
    // READ_ANYBODY, WRITE_ANYBODY
    0x0a, 0x00, 0x0e, 0x01, 0x0a, 0x00, 0x02, 0x29, 0x00, 0x00, 
    // END
    0x00, 0x00, 
}; // total size 71 bytes 


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
#define ATT_SERVICE_ORG_BLUETOOTH_SERVICE_PHYSICAL_ACTIVITY_MONITOR_START_HANDLE 0x0007
#define ATT_SERVICE_ORG_BLUETOOTH_SERVICE_PHYSICAL_ACTIVITY_MONITOR_END_HANDLE 0x000a
#define ATT_SERVICE_ORG_BLUETOOTH_SERVICE_PHYSICAL_ACTIVITY_MONITOR_01_START_HANDLE 0x0007
#define ATT_SERVICE_ORG_BLUETOOTH_SERVICE_PHYSICAL_ACTIVITY_MONITOR_01_END_HANDLE 0x000a

//
// list mapping between characteristics and handles
//
#define ATT_CHARACTERISTIC_GAP_DEVICE_NAME_01_VALUE_HANDLE 0x0003
#define ATT_CHARACTERISTIC_GATT_DATABASE_HASH_01_VALUE_HANDLE 0x0006
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_GENERAL_ACTIVITY_SUMMARY_DATA_01_VALUE_HANDLE 0x0009
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_GENERAL_ACTIVITY_SUMMARY_DATA_01_CLIENT_CONFIGURATION_HANDLE 0x000a
