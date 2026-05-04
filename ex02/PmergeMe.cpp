#include "PmergeMe.hpp"
#include "cstdlib"
#include <algorithm>
#include <numeric> //adjacent_difference

size_t insert(std::vector<int> const &chain, int value, size_t right);

PmergeMe::PmergeMe(std::vector<int> vect) : _init(vect)
{
	if (_init.size() < 2)
	{
		throw std::logic_error("Error: provide at least 2 numbers");
	}
	std::vector<int> tmp = _init;

	sort(tmp.begin(), tmp.end());
	std::adjacent_difference(tmp.begin(), tmp.end(), tmp.begin());
	if (*std::min_element(tmp.begin() + 1, tmp.end()) == 0)
	{
		throw std::logic_error("Error: no duplicate values allowed");
	}
}

PmergeMe::~PmergeMe() {}

std::vector<int> extractBigs(std::vector<Pair> const &pairs)
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
	while (jacob.back() < n)
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
	// std::cout << "build jacob: ";
	// printVector(res);
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
		insertOdd(sorted, odd);
	// std::cout << "print vector: ";
	// printVector(sorted);
	// std::cout << "\n";

	return sorted;
}

std::vector<size_t> PmergeMe::buildBigPositions(std::vector<int> const &chain,std::vector<Pair> const &pairs)
{
	std::vector<size_t> positions;
	size_t i;
	size_t j;

	i = 0;
	while (i < pairs.size())
	{
		j = 0;
		while (j < chain.size())
		{
			if (chain[j] == pairs[i].big)
			{
				positions.push_back(j);
				break;
			}
			j++;
		}
		i++;
	}
	return positions;
}

size_t PmergeMe::binaryInsert(std::vector<int> const &res, int value, size_t right)
{

	size_t left;
	size_t mid;

	left = 0;
	while (left < right)
	{
		mid = left + (right - left) / 2;
		if (res[mid] < value)
			left = mid + 1;
		else
			right = mid;
	}
	
	return left; // insert before pos
}

void PmergeMe::insertSmalls(std::vector<int> &result, std::vector<Pair> const &pairs)
{
	std::vector<size_t> order;
	std::vector<size_t> big_pos;
	size_t i;
	size_t j;
	size_t idx;
	size_t insert_pos;

	order = buildJacob(pairs.size());
	big_pos = buildBigPositions(result, pairs);

	i = 0;
	while (i < order.size())
	{
		idx = order[i];

		insert_pos = insert(result, pairs[idx].small, big_pos[idx]);

		result.insert(result.begin() + insert_pos, pairs[idx].small);

		j = 0;
		while (j < big_pos.size())
		{
			if (big_pos[j] >= insert_pos)
				big_pos[j]++;
			j++;
		}
		i++;
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

void PmergeMe::insertOdd(std::vector<int> &res, int value)
{
	std::vector<int>::iterator pos;

	pos = std::lower_bound(res.begin(), res.end(), value);
	res.insert(pos, value);
}