#include <iostream>
#include "random_value.h"

int check_value(int max)
{
	const int target_value = random_value(max);
	int current_value = 0;
	int score = 0; // same as user try count
	bool not_win = true;

	std::cout << "Enter your guess:" << std::endl;

	do
	{
		std::cin >> current_value;

		if (current_value > target_value)
		{
			std::cout << "less than " << current_value << std::endl;
		}
		else if (current_value < target_value)
		{
			std::cout << "greater than " << current_value << std::endl;
		}
		else
		{
			std::cout << "you win!"
					  << " attempts = " << score << std::endl;
			break;
		}

		score++;
	} while (true);

	return score;
}