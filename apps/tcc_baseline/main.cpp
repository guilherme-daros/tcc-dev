#include "pico/runtime.h"
#include "pico/stdlib.h"
#include "pico/time.h"

#include "btstack.h"
#include "pico/cyw43_arch.h"
#include "server_functions.h"

#include <array>
#include <chrono>
#include <iostream>

namespace {
// Logging stuff
constexpr int kBufferSize = 100;
char buf[kBufferSize];
constexpr int kTxFrequency = 40; // max_value = 40
constexpr int kTxInterval = 1000 * 1 / kTxFrequency;

//  Minimum advertising interval for undirected
//  and low duty cycle directed advertising.
//  Range: 0x0020 to 0x4000
//  Time = N * 0.625 ms
//  Time Range: 20 ms to 10.24 sec
//  Set to minimum because we're controlling this stuff with delays
constexpr uint16_t adv_interval =
    0x0020 + static_cast<int>((kTxInterval - 20) / 0.625);

} // namespace

int main() {
  stdio_init_all();
  sleep_ms(3000);

  printf("vish %d\n", kTxInterval);

  ble_init_all(adv_interval);
  hci_power_control(HCI_POWER_ON);

  while (true) {
    // adv_temp_humi_handler(&adv_temp_humi);
    // sleep_ms(50);
    // hci_power_control(HCI_POWER_OFF);
    // sleep_ms(kTxInterval);
    tight_loop_contents();
  }

  return 0;
}