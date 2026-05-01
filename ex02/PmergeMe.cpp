#include "PmergeMe.hpp"
#include "cstdlib"

PmergeMe::PmergeMe(char **av)
{
	int i = 1;
	int x;
	while (av[i] != NULL)
	{
		x = std::atoi(av[i]);
		_init.push_back(x);
		i++;
	}
}

PmergeMe::~PmergeMe(){}

std::ostream& operator<<(std::ostream& os, const Pair& pair)
{
	os << "(" << pair.a << ", " << pair.b << ")";
	return os;
}