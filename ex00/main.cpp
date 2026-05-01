#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <map>

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Error: use ./btc \"filename\"\n";
		return 1;
	}
	(void)av;
	std::string line;
	BitcoinExchange btx;

	btx.storeData("data.csv");
	btx.handleInput(av[1]);
}
