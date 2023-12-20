#include "config.h"
#include "log.h"

#include "pico/stdlib.h"

int main() {
  // stdio_init_all();
  while (true) {
    tight_loop_contents();
  }
}