
#include "PmergeMe.hpp"
#include "cstdlib"
#include <iostream>

void avInVect(char** av, std::vector<int>& vect);

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << "Error: you must provide a list of number\n";
	}
	std::vector<int> vect;
	avInVect(av, vect);

	try{

		std::vector<int> result;
		PmergeMe a(vect);
		a.printVector(a.getVector());
		result = a.mergeInsertion(a.getVector());
		
		a.printVector(result);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << "\n";
	}
	return 0;
}

void avInVect(char** av, std::vector<int>& vect)
{
	int i = 1;
	int x;
	while (av[i] != NULL)
	{
		x = std::atoi(av[i]);
		vect.push_back(x);
		i++;
	}
}
