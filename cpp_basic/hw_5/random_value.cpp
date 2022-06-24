#include <iostream>

#include <cstdlib>
#include <ctime>

int random_value()
{
	const int max_value = 100;

	std::srand(std::time(nullptr)); // use current time as seed for random generator

	return std::rand() % 100;
}