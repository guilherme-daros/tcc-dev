#include "log.h"
#include "pico/time.h"

namespace logger {
auto Log(const char *name) -> void {
  std::cout << "[ " << time_us_64() / 1e6 << " ] "
            << "Hello, " << name << std::endl;
}
} // namespace logger