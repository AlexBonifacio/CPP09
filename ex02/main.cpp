
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

	try
	{
		double start;
		double end;
		double elapsed_vector;
		double elapsed_deque;
		std::vector<int> res_vect;
		std::deque<int> res_deq;
		PmergeMe a(vect);
		
		
		start = getTime();
		res_vect = a.mergeInsertion(a.getVector());
		end = getTime();
		elapsed_vector = end - start;

		/* PRINT RESULTS */
		std::cout << "Before: " << std::setw(17);
		std::vector<int>::iterator it;
		it = vect.begin();
		while (it != vect.end())
		{
			std::cout << *it << " ";
			++it;
		}
		std::cout << "\n";
		std::cout << "After vector sort: " << std::setw(6);
		a.printVector(res_vect);
		/* END PRINTS */




		/* DEQUE */
		start = getTime();
		PmergeMe b(dq);
		res_deq = b.mergeInsertion(b.getDeque());
		end = getTime();
		elapsed_deque = end - start;
		std::cout << "After deque sort: " << std::setw(7);
		b.printVector(res_deq);

		/* VECTORS TIMER */
		std::cout << "Time to process a range of " << res_vect.size() << " elements with std::vector: "
				  << std::fixed << std::setprecision(2) << elapsed_vector << " us\n";
		/* DEQUE TIMER */
		std::cout << "Time to process a range of " << res_deq.size() << " elements with std::deque: "
				  << std::fixed << std::setprecision(2) << elapsed_deque << " us\n";
			
		std::cout << "Count insertions vector: " << a.getCount() << "\n";
		std::cout << "Count insertions deque:  " << b.getCount() << "\n";

	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << "\n";
	}
	return 0;
}

double getTime(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (static_cast<double>(tv.tv_sec) * 1000000.0 + static_cast<double>(tv.tv_usec));
}
