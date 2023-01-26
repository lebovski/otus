#include <thread>
#include <mutex>
#include <condition_variable>

#include <iostream>

std::condition_variable condition_variable;
std::mutex mutex;
bool notificated = false;

int global = 0;

void example() {

	std::thread thr1{
		[]() {
			while(true) {
				std::unique_lock<std::mutex> lck{mutex};
				std::cout << "Before waiting!" << std::endl;

				// guarded suspension
				// spurious invocation
				while(!notificated) condition_variable.wait(lck);

				// condition_variable.wait(lck,
				// 	[&notificated](){ return notificated; }
				// );

				std::cout << "After waiting!" << std::endl;
			}
		}
	};

	std::thread thr2 {
		[]() {
			std::unique_lock<std::mutex> lck{mutex};

			std::cout << "Before wake up" << std::endl;

			condition_variable.notify_one(); // .....
			notificated = true;

			std::cout << "After wake up" << std::endl;
		}
	};

	thr1.join();
	thr2.join();

}

int main() {

	example();

	return 0;
}