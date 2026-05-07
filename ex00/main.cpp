#include "BitcoinExchange.hpp"
#include "BitcoinValue.hpp"
#include <iostream>


int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Error: use ./btc \"filename\"\n";
		return 1;
	}

	try{

		BitcoinExchange btt("data.csv", av[1]);
	}
	catch (...)
	{
		return 1;
	}
}


// int main(int ac, char **av)
// {
// 	if (ac != 2)
// 	{
// 		std::cerr << "Error: use ./btc \"filename\"\n";
// 		return 1;
// 	}

// 	try{

// 		BitcoinExchange btt("data.csv", av[1]);
// 		std::cout << "\n";
// 		BitcoinValue a(btt.getTotalSpend(), btt.getBtcOwned());
// 	}
// 	catch (const std::exception& e)
// 	{
// 		std::cout << e.what() << "\n";
// 		return 1;
// 	}
// }

