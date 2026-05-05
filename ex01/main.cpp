
#include "RPN.hpp"
#include <iostream>

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cout << "Error: need one argument, usage: ./RPN \"a b +\"\n";
		return 1;
	}

	try{

		RPN rpn(av[1]);
		rpn.run();
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << "\n";
	}
	
	return 0;
}