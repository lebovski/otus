#include <array>
#include <future>
#include <iostream>
#include <vector>

void replace(std::vector<char> &buffer, const char new_symbol) {
  for (auto &ch : buffer) {
    ch = new_symbol;
  }
}

template <typename Source> void print(const Source &buffer) {
  for (const auto &ch : buffer) {
    std::cout << ch;
  }
  std::cout << std::endl;
}

int main() {
  std::vector<char> buffer(1'000, 'X');
  const auto new_symbols =
      std::array<char, 8>{'1', '2', '3', '4', '5', '6', '7', '8'};

  std::vector<std::future<void>> tasks;
  tasks.reserve(new_symbols.size());

  for (const auto &symbol : new_symbols) {
    tasks.emplace_back(std::async([&buffer, &symbol]() { replace(buffer, symbol); }));
  }

  for (const auto &task : tasks) {
    task.wait();
  }

  print(buffer);
}