#include <iostream>
#include <string>

int parce_args(int argc, char **argv, int *max, bool *table)
{
	if (argc >= 2)
	{
		std::string arg1_value{argv[1]};
		if (arg1_value == "-max")
		{
			int parameter_value = 0;
			if (argc < 3)
			{
				std::cout << "Wrong usage! The argument '-parameter' requires some value!" << std::endl;
				return -1;
			}

			*max = std::stoi(argv[2]);
		}

		if (arg1_value == "-table")
		{
			*table = true;
		}
	}

	return 0;
}