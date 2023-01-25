#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <future>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

bool is_prime(const size_t n) {
  if (n < 2) {
    return false;
  }

  for (size_t i = 2; i < n; ++i) {
    if (n % i == 0) {
      return false;
    }
  }

  return true;
}

size_t count_primes(size_t begin, const size_t end) {
  size_t count = 0;

  while (begin != end) {
    if (!is_prime(begin++)) {
      continue;
    }

    ++count;
  }

  return count;
}

int main(const int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " n [nthreads]" << std::endl;
    return EXIT_FAILURE;
  }
  const auto n = std::stoi(argv[1]);
  if (n <= 0) {
    std::cerr << "n must be positive number" << std::endl;
    return EXIT_FAILURE;
  }
  const int n_threads =
      argc > 2 ? std::stoi(argv[2])
               : static_cast<int>(std::thread::hardware_concurrency());
  if (n_threads < 1) {
    std::cerr << "nthreads must be positive number" << std::endl;
    return EXIT_FAILURE;
  }

  const int batch_size = n / n_threads;

  std::vector<std::future<size_t>> tasks;
  tasks.reserve(n);

  const auto start = std::chrono::high_resolution_clock::now();

  for (int i = 2; i < n; i += batch_size) {
    const auto end = std::min<size_t>(n, i + batch_size);

    // Launches new async task for count_primes.
    auto task = std::async(std::launch::async, count_primes, i, end);

    // Saving the async task feature in the list of tasks.
    tasks.push_back(std::move(task));
  }

  size_t nPrimes = 0;
  for (auto &task : tasks) {
    nPrimes += task.get(); // <--- waits for current task, but pauses no one
  }

  const auto end = std::chrono::high_resolution_clock::now();
  const auto elapsed = end - start;
  const auto elapsedSeconds =
      std::chrono::duration_cast<std::chrono::seconds>(elapsed);

  std::cout << "Result: " << nPrimes << std::endl;
  std::cout << "It took " << elapsedSeconds.count() << " seconds with "
            << n_threads << " threads" << std::endl;

  return EXIT_SUCCESS;
}