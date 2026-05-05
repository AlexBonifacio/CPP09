#pragma once

#include <vector>
#include <deque>
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
	PmergeMe(std::deque<int> dq);
	~PmergeMe();
	template <typename T>
	void printVector(const std::vector<T> &vect)
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

	const std::vector<int> &getVector() const
	{
		return _init;
	}

	const std::deque<int> &getDeque() const
	{
		return _dq;
	}

	std::vector<int> mergeInsertion(std::vector<int> input);
	std::deque<int> mergeInsertion(std::deque<int> input);

private:
	const std::vector<int> _init;
	const std::deque<int> _dq;

	PmergeMe();
	PmergeMe(const PmergeMe &copy);
	PmergeMe &operator=(const PmergeMe &other);

	// vector
	std::vector<Pair> makePair(const std::vector<int> &input);
	std::vector<int> extractBigs(std::vector<Pair> const &pairs);
	std::vector<size_t> buildJacob(size_t i);
	std::vector<size_t> buildBigPositions(std::vector<int> const &result, std::vector<Pair> const &pairs);
	void insertOdd(std::vector<int> &res, int value);
	void insertSmalls(std::vector<int> &result, std::vector<Pair> const &pairs);
	size_t binaryInsert(std::vector<int> const &res, int value, size_t right);

	// deque
	std::deque<Pair> makePair(const std::deque<int> &input);
	std::deque<int> extractBigs(std::deque<Pair> const &pairs);
	std::vector<size_t> buildBigPositions(std::deque<int> const &result, std::deque<Pair> const &pairs);
	void insertOdd(std::deque<int> &res, int value);
	void insertSmalls(std::deque<int> &result, std::deque<Pair> const &pairs);
	size_t binaryInsert(std::deque<int> const &res, int value, size_t right);
};

std::ostream &operator<<(std::ostream &os, const Pair &pair);