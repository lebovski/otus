#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

class ThreadGuard {
public:
  explicit ThreadGuard(std::thread &thread) : m_thread{thread} {}

  ThreadGuard(const ThreadGuard &) = delete;
  ThreadGuard(ThreadGuard &&) = delete;
  ThreadGuard &operator=(const ThreadGuard &) = delete;
  ThreadGuard &operator=(ThreadGuard &&) = delete;

  ~ThreadGuard() {
    if (m_thread.joinable()) {
      std::cout << "Joining..." << std::endl;
      m_thread.join();

      std::cout << "Completed." << std::endl;
    }
  }

private:
  std::thread &m_thread;
};

void foo() {
  using namespace std::chrono_literals;

  std::this_thread::sleep_for(10000ms);
}

int main(const int argc, const char *argv[]) {
  std::thread thread{foo};

  const ThreadGuard guard{thread};

  if (argc > 1 && argv != nullptr) {
    std::cout << "Exit case 1" << std::endl;

    return EXIT_SUCCESS; // will wait thread here
  }

  std::cout << "Exit case 2" << std::endl;

  return EXIT_SUCCESS; // will wait thread here too
}
