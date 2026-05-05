
#include "PmergeMe.hpp"
#include <cstdlib>
#include <iostream>
#include <sys/time.h> //gettimeofday
#include <iomanip>	  // setprecision
#include <vector>

double getTime(void);

template <typename Container>
void avInContainer(char **av, Container &vect)
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

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << "Error: you must provide a list of number\n";
	}

	std::vector<int> vect;
	std::deque<int> dq;
	avInContainer(av, vect);
	avInContainer(av, dq);

	
	std::cout << "Before: " << std::setw(5);
	std::vector<int>::iterator it;
	it = vect.begin();
	while (it != vect.end())
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << "\n";

	try
	{

		double start;
		double end;
		double elapsed;
		start = getTime();

		std::vector<int> result;
		PmergeMe a(vect);

		result = a.mergeInsertion(a.getVector());
		end = getTime();
		elapsed = end - start;

		std::cout << "After: " << std::setw(5);
		a.printVector(result);

		std::cout << "Time to process a range of " << result.size() << " elements with std::vector: "
				  << std::fixed << std::setprecision(2) << elapsed << " us\n";

		start = getTime();
		std::deque<int> res_deq;
		PmergeMe b(dq);
		res_deq = b.mergeInsertion(b.getDeque());
		end = getTime();
		elapsed = end - start;
		std::cout << "Time to process a range of " << res_deq.size() << " elements with std::deque: "
				  << std::fixed << std::setprecision(2) << elapsed << " us\n";
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << "\n";
	}
	return 0;
}

double getTime(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (static_cast<double>(tv.tv_sec) * 1000000.0 + static_cast<double>(tv.tv_usec));
}
