#include "config.h"
#include "log.h"

#include "pico/stdlib.h"

int main() {
  stdio_init_all();
  while (true) {
    log::Log(config::name);
    sleep_ms(1000);
  }
}