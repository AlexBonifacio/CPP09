#include "RPN.hpp"
#include <iostream>
#include <cctype>
#include <exception>

RPN::RPN(const std::string input) : _expr(input) {};

RPN::~RPN() {};

static bool isOperator(const char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

int RPN::selectOperator(const char c, int a, int b)
{
	if (c == '+')
		return a + b;
	if (c == '-')
		return a - b;
	if (c == '*')
		return a * b;
	if (c == '/')
	{
		if (b == 0)
		{
			throw std::logic_error("Error: division by zero");
		}
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