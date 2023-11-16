#include "log.h"
#include "pico/time.h"
#include <iostream>

namespace logger {
auto Log(const char *msg) -> void {
  std::cout << "[ " << time_us_64() / 1e6 << " ] " << msg << std::endl;
}

} // namespace logger