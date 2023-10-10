#include "log.h"
#include "pico/time.h"

namespace log {
auto Log(const char *name) -> void {
  std::cout << "[ " << time_us_32() / 1e6 << " ] "
            << "Hello, " << name << std::endl;
}

} // namespace log