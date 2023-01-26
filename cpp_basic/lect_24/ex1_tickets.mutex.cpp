// Emulation of tickets selling system

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <random>
#include <string>
#include <thread>

const int initial_tickets_count = 10;
const double lambda = 10; // mean tickets sold per second

void usefull_work() {
  using namespace std::chrono_literals;
  std::random_device rd;
  std::default_random_engine gen(rd());
  std::exponential_distribution<> dist(lambda);
  std::this_thread::sleep_for(dist(gen) * 1s);
}

// Recursive lock!
// void update_book(const std::string_view &op_name, std::recursive_mutex &rmtx)
// {
//   rmtx.lock();
//   // ...
//   rmtx.unlock();
// }

void cacher(int &tickets_left, std::mutex &mtx) {
  for (;;) {
    usefull_work();

    mtx.lock();
    try {
      if (tickets_left == 0) {
        mtx.unlock();
        break;
      }

      // Lock inner
      // update_book("123", mtx);
      --tickets_left;
    } catch (...) {
      mtx.unlock();
      throw;
    }

    mtx.unlock();
    usefull_work();
  }
}

int main(int argc, char *argv[]) {
  using namespace std;
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " [number of cashiers]\n";
    return EXIT_FAILURE;
  }

  int ncahshiers = stoi(argv[1]);
  if (ncahshiers < 1) {
    cerr << "number of cashiers must be positive integer\n";
    return EXIT_FAILURE;
  }

  int tickets = initial_tickets_count;
  std::mutex mtx;
  std::vector<std::thread> cachiers;
  for (int i = 0; i < ncahshiers; ++i) {
    cachiers.emplace_back(cacher, ref(tickets), ref(mtx));
  }

  for (auto &cachier : cachiers) {
    cachier.join();
  }
  cout << "Tickets left: " << tickets << '\n';
}
