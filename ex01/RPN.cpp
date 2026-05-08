#include "RPN.hpp"
#include <iostream>
#include <cctype>
#include <exception>
#include <limits>

RPN::RPN(const std::string &input) : _expr(input) {};

RPN::~RPN() {};

static bool isOperator(const char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

// min / max -10 / 9
int RPN::selectOperator(const char c, int a, int b)
{
	if (c == '+')
	{
		if ((b > 0 && a > std::numeric_limits<int>::max() - b) || (b < 0 && a < std::numeric_limits<int>::min() - b))
		{
			throw std::logic_error("Error: overflow");
		}
		return a + b;
	}
	if (c == '-') // a - b | b = -1 a = 10 -> 11 | b = 1 a = -10
	{
		if ((b < 0 && a > std::numeric_limits<int>::max() + b) || (b > 0 && a < std::numeric_limits<int>::min() + b))
		{
			throw std::logic_error("Error: overflow");
		}
		return a - b;
	}
	if (c == '*')
	{
		if (a != 0 && b != 0)
		{
			if (a == -1 && b == std::numeric_limits<int>::min()) // -1 * -10
				throw std::logic_error("Error: overflow");
			if (b == -1 && a == std::numeric_limits<int>::min()) 
				throw std::logic_error("Error: overflow");
			if (a > 0 && b > 0 && a > std::numeric_limits<int>::max() / b) 
				throw std::logic_error("Error: overflow");
			if (a > 0 && b < 0 && b < std::numeric_limits<int>::min() / a)
				throw std::logic_error("Error: overflow");
			if (a < 0 && b > 0 && a < std::numeric_limits<int>::min() / b)
				throw std::logic_error("Error: overflow");
			if (a < 0 && b < 0 && a < std::numeric_limits<int>::max() / b)
				throw std::logic_error("Error: overflow");
		}
		return a * b;
	}
	if (c == '/')
	{
		if (b == 0)
		{
			throw std::logic_error("Error: division by zero");
		}
		if (a == std::numeric_limits<int>::min() && b == -1) // -10 / -1
			throw std::logic_error("Error: overflow");
		return a / b;
	}
	throw std::logic_error("Error: invalid operator");
}

void RPN::run()
{
	int i;

	i = 0;

	while (_expr[i] != '\0')
	{
		if (std::isdigit(static_cast<unsigned char>(_expr[i])))
		{
			stck.push(_expr[i] - '0');
		}
		else if (isOperator(_expr[i]))
		{
			if (stck.size() < 2)
			{
				throw std::logic_error("Error: not enough operands");
			}
			int a, b, res;

			b = stck.top();
			stck.pop();
			a = stck.top();
			stck.pop();

			res = selectOperator(_expr[i], a, b);
			stck.push(res);
		}
		else if (_expr[i] != ' ')
		{
			throw std::logic_error("Error: invalid token");
		}
		++i;
	}

	if (stck.size() == 1)
		std::cout << stck.top() << "\n";
	else
	{
		throw std::logic_error("Error: invalid arguments");
	}
}