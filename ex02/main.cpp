
#include "PmergeMe.hpp"
#include <iostream>

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << "Error: you must provide a list of number\n";
	}

	std::vector<int> result;
	PmergeMe a(av);
	a.printVector(a.getVector());
	result = a.mergeInsertion(a.getVector());

	a.printVector(result);
	return 0;
}