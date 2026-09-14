

#include <chrono>
#include <csignal>
#include <fstream>
#include <iostream>
#include <thread>

namespace {
constexpr const char *g_ledPath = "/sys/class/leds/red:user/brightness";

bool write_led(int value) {
  std::ofstream led_file(g_ledPath);
  if (!led_file.is_open()) {
    std::cerr << "Failed to open LED brightness file: " << g_ledPath << "\n";
    return false;
  }

  led_file << value << '\n';
  if (!led_file) {
    std::cerr << "Failed to write brightness value " << value << " to "
              << g_ledPath << "\n";
    return false;
  }

  return true;
}
} // namespace

int main() {
  std::cout << "Toggling " << g_ledPath << " (Ctrl+C to stop)\n";

  while (true) {
    if (!write_led(1)) {
      return 1;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));

    if (!write_led(0)) {
      return 1;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  if (!write_led(0)) {
    return 1;
  }

  return 0;
}