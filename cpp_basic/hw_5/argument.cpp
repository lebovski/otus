#include <iostream>
#include <string>

int main(int argc, char **argv)
{
	// argc - it is a count of arguments
	// But there is some detail - OS always pass one system argument - the name of the executable
	// So, is the application was executed without arguments at all, argc will be still == 1

	// Let's print this argument
	if (argc > 0)
	{
		std::cout << "We have at least one argument!" << std::endl;
		std::cout << "argv[0] = " << argv[0] << std::endl;
	}

	// To check - does use print some other argument we should check if the argc >= 2
	if (argc >= 2)
	{
		std::cout << "We have one more argument!" << std::endl;
		std::cout << "argv[1] = " << argv[1] << std::endl;

		std::string arg1_value{argv[1]};
		if (arg1_value == "-parameter")
		{
			std::cout << "-parameter argument was detected!" << std::endl;

			// We've detected the '-parameter' argument. And we extect that after this argument there is a value:
			int parameter_value = 0;
			if (argc < 3)
			{
				std::cout << "Wrong usage! The argument '-parameter' requires some value!" << std::endl;
				return -1;
			}
			// We need to parse the string to the int value
			parameter_value = std::stoi(argv[2]);
			std::cout << "The '-parameter' value = " << parameter_value << std::endl;
		}
	}

	return 0;
}