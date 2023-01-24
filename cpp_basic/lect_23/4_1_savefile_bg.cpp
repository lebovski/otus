#include <cstddef>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <thread>
#include <vector>

#if defined(__linux__) || defined(__APPLE__)
const char *const null = "/dev/null";
#elif defined(_WIN32)
const char *const null = "NUL";
#else
#error Platform not supported.
#endif

std::thread savefile_bg(const std::string &filename) {
  auto write = [](const std::string filename) {
    std::vector<char> buffer(10 * 4096 * 4096, 'A');

    std::ofstream out{filename};
    out.write(buffer.data(), static_cast<std::streamsize>(buffer.size()));
    out.close();

    std::clog << "File written." << std::endl;
  };

  return std::thread(std::move(write), filename);
}

int main() {
  std::thread bg_task = savefile_bg(null);

  bg_task.detach();

  std::getchar();
}
