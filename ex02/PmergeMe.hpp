#pragma once

#include <vector>
#include <iostream>

struct Pair
{
	int big;
	int small;
};


class PmergeMe
{
	public:
		PmergeMe(std::vector<int> vect);
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

		std::vector<Pair> makePair(const std::vector<int>& input);
		std::vector<int> mergeInsertion(std::vector<int> input);
		void insertSmalls(std::vector<int>& result, std::vector<Pair> const& pairs);
		std::vector<size_t> buildJacob(size_t i);

	private:
		const std::vector<int> _init;

		PmergeMe();
		PmergeMe(const PmergeMe& copy);
		PmergeMe& operator=(const PmergeMe& other);
};

std::ostream& operator<<(std::ostream& os, const Pair& pair);