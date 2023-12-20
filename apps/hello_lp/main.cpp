#include "hardware/clocks.h"
#include "hardware/rosc.h"
#include "hardware/structs/scb.h"
#include "hardware/watchdog.h"

#include "pico/cyw43_arch.h"
#include "pico/sleep.h"
#include "pico/stdlib.h"

#include <stdint.h>
#include <stdlib.h>

void cb(void){};

void recover_from_sleep(uint scb_orig, uint clock0_orig, uint clock1_orig) {

  // Re-enable ring Oscillator control
  rosc_write(&rosc_hw->ctrl, ROSC_CTRL_ENABLE_BITS);

  // reset procs back to default
  scb_hw->scr = scb_orig;
  clocks_hw->sleep_en0 = clock0_orig;
  clocks_hw->sleep_en1 = clock1_orig;

  // reset clocks
  clocks_init();
  stdio_init_all();

  return;
}

int main() {
  if (cyw43_arch_init()) {
    return -1;
  }

  // save values for later
  uint scb_orig = scb_hw->scr;
  uint clock0_orig = clocks_hw->sleep_en0;
  uint clock1_orig = clocks_hw->sleep_en1;

  // crudely reset the clock each time
  // to the value below
  datetime_t t = {.year = 2020,
                  .month = 06,
                  .day = 05,
                  .dotw = 5, // 0 is Sunday, so 5 is Friday
                  .hour = 15,
                  .min = 45,
                  .sec = 00};

  datetime_t t_alarm = {.year = 2020,
                        .month = 06,
                        .day = 05,
                        .dotw = 5, // 0 is Sunday, so 5 is Friday
                        .hour = 15,
                        .min = 45,
                        .sec = 10};

  // Start the Real time clock
  rtc_init();

  cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
  sleep_ms(5000);

  cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
  sleep_run_from_xosc();
  rtc_set_datetime(&t);
  sleep_goto_sleep_until(&t_alarm, cb);
  recover_from_sleep(scb_orig, clock0_orig, clock1_orig);

  cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
  while (true) {
    tight_loop_contents();
  };
}