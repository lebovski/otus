#include <iostream>
#include <thread>

int main() {

	auto lambda = [](std::thread &other) {
		while (!other.joinable())
			std::this_thread::yield();
		other.join();
	};

	std::thread first;
	std::thread second;

	first = std::thread{lambda, std::ref(second)};
	second = std::thread{lambda, std::ref(first)};

	std::cout << "before sleep" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "after sleep" << std::endl;

	if (first.joinable()) first.join();
	if (second.joinable()) second.join();

	return 0;
}