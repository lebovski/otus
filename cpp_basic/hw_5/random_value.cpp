#include <iostream>

#include <cstdlib>
#include <ctime>

int random_value(int max)
{
	std::srand(std::time(nullptr)); // use current time as seed for random generator

	return std::rand() % max;
}