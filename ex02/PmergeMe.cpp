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

PmergeMe::~PmergeMe() {}

// void PmergeMe::fj()
// {
// 	if (input.size() <= 1)
// 		return;

// 	makePair(input);
// 	std::vector<int> bigs;

// 	std::vector<int> sorted_bigs = mergeInsertion(bigs);

// }

void insert(std::vector<int> &result, int small)
{

	std::vector<int>::iterator pos;

	pos = std::lower_bound(result.begin(), result.end(), small); // pos not less than small
	result.insert(pos, small);									 // insert before pos
}


std::vector<int> extractBigs(std::vector<Pair> pairs)
{
	std::vector<int> bigs;

	size_t i = 0;
	size_t size = pairs.size();

	while (i < size)
	{
		bigs.push_back(pairs[i].big);
		++i;
	}
	return bigs;
}

/*
jacob 0,1,1,3,5,11
 order insertation, 1,3,2,5,4,11,10,9,8,7,6


*/
std::vector<size_t> PmergeMe::buildJacob(size_t n)
{
	std::vector<size_t> res;
	std::vector<size_t> jacob;
	size_t y = 0;

	jacob.push_back(0);
	jacob.push_back(1);
	y = 1;
	while(jacob.back() < n)
	{
		jacob.push_back(jacob[y - 1] * 2 + jacob[y]);
		++y;
	}

	size_t i = 1;
	size_t size = jacob.size();
	while (i < size)
	{
		y = jacob[i];
		while (y > jacob[i - 1])
		{
			if (y - 1 < n)
			{
				res.push_back(y - 1);
			}
			--y;
		}
		++i;
	}
	std::cout << "build jacob: ";
	printVector(res);
	std::cout << "\n";
	return res;
}

std::vector<int> PmergeMe::mergeInsertion(std::vector<int> input)
{
	bool is_odd = false;
	int odd = 0;

	if (input.size() <= 1)
		return input;

	if (input.size() % 2 != 0)
	{
		is_odd = true;
		odd = input[input.size() - 1];
	}
	std::vector<Pair> pairs = makePair(input);

	std::vector<int> bigs = extractBigs(pairs);

	std::vector<int> sorted = mergeInsertion(bigs);

	insertSmalls(sorted, pairs);
	if (is_odd)
		insert(sorted, odd);
	std::cout << "print vector: ";
	printVector(sorted);
	std::cout << "\n";

	return sorted;
}


void PmergeMe::insertSmalls(std::vector<int> &result, std::vector<Pair> const &pairs)
{
	size_t i, size;

	i = 0;
	size = pairs.size();
	buildJacob(size);
	while (i < size)
	{
		insert(result, pairs[i].small);
		++i;
	}
}

std::vector<Pair> PmergeMe::makePair(const std::vector<int> &input)
{
	const size_t size = input.size();
	std::vector<Pair> pairs;

	size_t i = 0;
	while (i < size)
	{
		if (i + 1 < size)
		{
			struct Pair pair;
			if (input[i] > input[i + 1])
			{
				pair.big = input[i];
				pair.small = input[i + 1];
			}
			else
			{
				pair.big = input[i + 1];
				pair.small = input[i];
			}
			pairs.push_back(pair);
			++i;
		}
		++i;
	}
	return pairs;
}

std::ostream &operator<<(std::ostream &os, const Pair &pair)
{
	os << "(" << pair.big << ", " << pair.small << ")";
	return os;
}
