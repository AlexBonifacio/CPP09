#include "PmergeMe.hpp"
#include <cstdlib>
#include <algorithm>
#include <numeric> //adjacent_difference

PmergeMe::PmergeMe(std::vector<int> vect) : _count(0), _init(vect)
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
	if (*tmp.begin() < 0)
	{
		throw std::logic_error("Error: no negative value allowed");
	}
}

PmergeMe::~PmergeMe() {}

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

	std::vector<Pair> ordered_pairs = reorderPairs(sorted, pairs);
	insertSmalls(sorted, ordered_pairs, is_odd, odd);
	// std::cout << "print vector: ";
	// printVector(sorted);
	// std::cout << "\n";

	return sorted;
}

std::vector<Pair> PmergeMe::makePair(const std::vector<int> &input)
{
	const size_t size = input.size();
	std::vector<Pair> pairs;
	struct Pair pair;

	size_t i = 0;
	while (i < size)
	{
		if (i + 1 < size)
		{
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
			++_count;
		}
		++i;
	}
	return pairs;
}

std::vector<int> PmergeMe::extractBigs(std::vector<Pair> const &pairs)
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

void PmergeMe::insertSmalls(std::vector<int> &result, std::vector<Pair> const &pairs, bool is_odd, int odd)
{
	std::vector<size_t> order;
	std::vector<size_t> big_pos;
	size_t i;
	size_t j;
	size_t idx;
	size_t insert_pos;
	size_t order_size;

	order = buildJacob(pairs.size() + static_cast<size_t>(is_odd));
	big_pos = buildBigPositions(result, pairs); // looking at ordered result return the current position of each big in pair

	i = 0;
	order_size = order.size();
	while (i < order_size)
	{
		idx = order[i];
		if (idx < pairs.size())
		{
			// std::cout << "b" << idx + 1
			// 		  << " value: " << pairs[idx].small
			// 		  << " | right: " << big_pos[idx]
			// 		  << "\n";
			insert_pos = binaryInsert(result, pairs[idx].small, big_pos[idx]);
			result.insert(result.begin() + insert_pos, pairs[idx].small);
		}
		else
		{

			// std::cout << "odd value: " << odd
			// 		  << " | current size: " << result.size()
			// 		  << "\n";
			insert_pos = binaryInsert(result, odd, result.size());
			result.insert(result.begin() + insert_pos, odd);
		}

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

// suit: 0 1 1 3 5 11
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
	std::cout << "build jacob: ";
	printVector(res);
	return res;
}

std::vector<size_t> PmergeMe::buildBigPositions(std::vector<int> const &result, std::vector<Pair> const &pairs)
{
	std::vector<size_t> positions;
	size_t i;
	size_t j;

	// (8 5) (7 3) 	pairs
	// 7 8 			result
	i = 0;
	while (i < pairs.size())
	{
		j = 0;
		while (j < result.size())
		{
			if (result[j] == pairs[i].big)
			{
				positions.push_back(j);
				break;
			}
			j++;
		}
		i++;
	}
	// 1 0 position
	return positions;
}

std::vector<Pair> PmergeMe::reorderPairs(std::vector<int> const &sorted, std::vector<Pair> const &pairs)
{
	std::vector<Pair> ordered;
	size_t i;
	size_t j;

	i = 0;
	while (i < sorted.size())
	{
		j = 0;
		while (j < pairs.size())
		{
			if (pairs[j].big == sorted[i])
			{
				ordered.push_back(pairs[j]);
				break;
			}
			j++;
		}
		i++;
	}
	return ordered;
}

size_t PmergeMe::binaryInsert(std::vector<int> const &res, int value, size_t right)
{
	size_t left;
	size_t mid;

	left = 0;
	while (left < right)
	{
		++_count;
		mid = left + (right - left) / 2;
		if (res[mid] < value)
			left = mid + 1;
		else
			right = mid;
	}

	return left; // insert before pos
}

std::ostream &operator<<(std::ostream &os, const Pair &pair)
{
	os << "(" << pair.big << ", " << pair.small << ")";
	return os;
}

//  9 8 7 6 5 4 3 2 1 0 19
// 18 17 16 15 14 13 12 11 10 20

/*---------------------------------------------------------*/
/*DEQUE*/
/*---------------------------------------------------------*/

PmergeMe::PmergeMe(std::deque<int> dq) : _count(0), _dq(dq)
{
	if (_dq.size() < 2)
	{
		throw std::logic_error("Error: provide at least 2 numbers deque");
	}
	std::deque<int> tmp = _dq;

	sort(tmp.begin(), tmp.end());
	std::adjacent_difference(tmp.begin(), tmp.end(), tmp.begin());
	if (*std::min_element(tmp.begin() + 1, tmp.end()) == 0)
	{
		throw std::logic_error("Error: no duplicate values allowed");
	}
	if (*tmp.begin() < 0)
	{
		throw std::logic_error("Error: no negative value allowed");
	}
}

std::deque<int> PmergeMe::mergeInsertion(std::deque<int> input)
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
	std::deque<Pair> pairs = makePair(input);

	std::deque<int> bigs = extractBigs(pairs);

	std::deque<int> sorted = mergeInsertion(bigs);

	std::deque<Pair> ordered_pairs = reorderPairs(sorted, pairs);

	insertSmalls(sorted, ordered_pairs, is_odd, odd);
	// std::cout << "print vector: ";
	// printVector(sorted);
	// std::cout << "\n";

	return sorted;
}

std::deque<Pair> PmergeMe::makePair(const std::deque<int> &input)
{
	const size_t size = input.size();
	std::deque<Pair> pairs;
	struct Pair pair;

	size_t i = 0;
	while (i < size)
	{
		if (i + 1 < size)
		{
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
			++_count;
		}
		++i;
	}
	return pairs;
}

std::deque<int> PmergeMe::extractBigs(std::deque<Pair> const &pairs)
{
	std::deque<int> bigs;

	size_t i = 0;
	size_t size = pairs.size();

	while (i < size)
	{
		bigs.push_back(pairs[i].big);
		++i;
	}
	return bigs;
}

void PmergeMe::insertSmalls(std::deque<int> &result, std::deque<Pair> const &pairs, bool is_odd, int odd)
{
	std::vector<size_t> order;
	std::vector<size_t> big_pos;
	size_t i;
	size_t j;
	size_t idx;
	size_t insert_pos;
	size_t order_size;

	order = buildJacob(pairs.size() + static_cast<size_t>(is_odd));
	big_pos = buildBigPositions(result, pairs); // looking at ordered result return the current position of each big in pair

	i = 0;
	order_size = order.size();
	while (i < order_size)
	{
		idx = order[i];
		if (idx < pairs.size())
		{
			insert_pos = binaryInsert(result, pairs[idx].small, big_pos[idx]);
			result.insert(result.begin() + insert_pos, pairs[idx].small);
		}
		else
		{
			insert_pos = binaryInsert(result, odd, result.size());
			result.insert(result.begin() + insert_pos, odd);
		}

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

std::vector<size_t> PmergeMe::buildBigPositions(std::deque<int> const &result, std::deque<Pair> const &pairs)
{
	std::vector<size_t> positions;
	size_t i;
	size_t j;

	// (8 5) (7 3) 	pairs
	// 7 8 			result
	i = 0;
	while (i < pairs.size())
	{
		j = 0;
		while (j < result.size())
		{
			if (result[j] == pairs[i].big)
			{
				positions.push_back(j);
				break;
			}
			j++;
		}
		i++;
	}
	// 1 0 position
	return positions;
}

std::deque<Pair> PmergeMe::reorderPairs(std::deque<int> const &sorted, std::deque<Pair> const &pairs)
{
	std::deque<Pair> ordered;
	size_t i;
	size_t j;

	i = 0;
	while (i < sorted.size())
	{
		j = 0;
		while (j < pairs.size())
		{
			if (pairs[j].big == sorted[i])
			{
				ordered.push_back(pairs[j]);
				break;
			}
			j++;
		}
		i++;
	}
	return ordered;
}

size_t PmergeMe::binaryInsert(std::deque<int> const &res, int value, size_t right)
{

	size_t left;
	size_t mid;

	left = 0;
	while (left < right)
	{
		++_count;
		mid = left + (right - left) / 2;
		if (res[mid] < value)
			left = mid + 1;
		else
			right = mid;
	}

	return left; // insert before pos
}

size_t PmergeMe::getCount() const
{
	return _count;
}

const std::vector<int> &PmergeMe::getVector() const
{
	return _init;
}

const std::deque<int> &PmergeMe::getDeque() const
{
	return _dq;
}