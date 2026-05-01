#pragma once

#include <vector>
#include <iostream>

struct Pair
{
	int a;
	int b;
};

class PmergeMe
{
	public:
		PmergeMe(char **av);
		~PmergeMe();
		template<typename T>
		void printVector(const std::vector<T>& vect)
		{
			typename std::vector<T>::const_iterator it;
			it = vect.begin();
			while (it != vect.end())
			{
				std::cout << *it << " ";
				++it;
			}
			std::cout << "\n";
		}

		const std::vector<int>& getVector() const
		{
			return _init;
		}

		const std::vector<Pair>& getPairVect() const {return _pair;};

	private:
		std::vector<Pair> _pair;
		std::vector<int> _init;
		PmergeMe();
		PmergeMe(const PmergeMe& copy);
		PmergeMe& operator=(const PmergeMe& other);
};

std::ostream& operator<<(std::ostream& os, const Pair& pair);