#include "logger.h"

#include "pico/time.h"

namespace logger {
auto Log(const std::string &msg) -> void {
  std::cout << "[ " << time_us_64() / 1e6 << " ] " << msg << std::endl;
}
} // namespace logger