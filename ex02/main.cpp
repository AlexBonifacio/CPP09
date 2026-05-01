
#include "PmergeMe.hpp"
#include <iostream>

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << "Error: you must provide a list of number\n";
	}
	PmergeMe a(av);
	a.printVector(a.getVector());
	return 0;
}