#include "btstack.h"
#include "log.h"
#include "math.h"
#include "physical_activity_monitor.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include "server_functions.h"
#include <stdio.h>

int main() {
  stdio_init_all();
  int led_on = true;
  sleep_ms(2000);

  init_ble_service();

  // while (true) {
  //   led_on = !led_on;
  //   cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
  //   sleep_ms(1000);
  //
  while (true) {
    tight_loop_contents();
  }

  return 0;
}