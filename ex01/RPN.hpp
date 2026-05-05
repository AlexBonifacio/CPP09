#pragma once
#include <string>
#include <stack>

class RPN
{
	public:
		RPN(const std::string input);
		~RPN();
		void run();

	private:
		std::stack<int> stck;
		std::string _expr;
		RPN();
		RPN(const RPN& copy);
		RPN& operator=(const RPN& other);

		int selectOperator(const char c, int a, int b);
};