#include "BitcoinExchange.hpp"
#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <sstream>

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string& datas, const std::string& invest_file) : _total_spend(0), _btc_owned(0)
{
	if (!storeData(datas))
		throw std::exception();
	if (!handleInput(invest_file))
		throw std::exception();
}


bool BitcoinExchange::storeData(const std::string &filename)
{
	std::string line;
	std::ifstream file(filename.c_str()); // input file stream
	size_t pos;
	std::string key;
	std::string s_value;
	double value;
	char *end;
	size_t i;

	_data_map.clear();
	if (!file.is_open())
	{
		std::cerr << "Fail to open " << filename << "\n";
		return false;
	}
	std::getline(file, line);
	i = 2;
	while (std::getline(file, line))
	{
		// std::cout << line << "\n";
		pos = line.find(",");
		if (pos == std::string::npos)
		{
			file.close();
			std::cerr << "Error: ',' not found \"" << filename << "\", line:  " << i << "\n";
			return false;
		}
		key = line.substr(0, pos);
		s_value = line.substr(pos + 1);
		errno = 0;
		value = std::strtod(s_value.c_str(), &end);
		if (errno != 0 || *end != '\0' || value < 0)
		{
			file.close();
			std::cerr << "Error: invalid value in \"" << filename << "\", line:  " << i << "\n";
			return false;
		}
		_data_map[key] = value;
		++i;
	}
	// printMap(_data_map);
	file.close();
	return true;
}

// we are looking for the first char and the last char
// first -> if there is no char the line is empty
// last -> there is at least something
// str = start pos + len 
void trim(std::string &str)
{
	size_t first;
	size_t last;

	first = str.find_first_not_of(" \t");
	if (first == std::string::npos)
	{
		str.clear();
		return;
	}
	last = str.find_last_not_of(" \t");
	str = str.substr(first, last - first + 1);
}

#include <climits>
bool BitcoinExchange::isValidValue(std::string &value_str, double &value, const std::string &str)
{
	errno = 0;
	char *end;

	value = std::strtod(value_str.c_str(), &end);
	if (errno != 0 || *end != '\0')
	{
		std::cerr << "Error: invalid value at " << str << "\n";
		return false;
	}
	else if (value < 0)
	{
		std::cerr << "Error: not a positive value at " << str << "\n";
		return false;
	}
	else if (value > 1000)
	{
		std::cerr << "Error: too large number at " << str << "\n";
		return false;
	}

	return true;
}

bool BitcoinExchange::parseLine(std::string &line, std::string &date, std::string &value_str)
{
	size_t pos;
	std::stringstream ss(line);
	(void)value_str;

	if (line.empty())
		return false;

	pos = line.find("|");
	if (pos == std::string::npos)
	{
		std::cerr << "Error: missing separator \'|\'\n";
		return false;
	}

	if (!std::getline(ss, date, '|'))
	{
		std::cerr << "Error: bad input => " << line << "\n";
		return false;
	}

	trim(date);
	if (!std::getline(ss, value_str))
	{
		std::cerr << "Error: bad input => " << line << "\n";
		return false;
	}
	if (value_str.empty())
	{
		std::cerr << "Error: bad input => " << line << "\n";
		return false;
	}
	trim(value_str);
	return true;
}

int leapYear(int year)
{
	if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
	{
		return 29;
	}
	return 28;
}
int daysInMonth(int year, int month)
{
	if (month == 2)
	{
		return leapYear(year);
	}
	if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		return 30;
	}
	return 31;
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
	std::stringstream ss(date);
	int y, m, d;
	char sep1, sep2;

	ss >> y >> sep1 >> m >> sep2 >> d;

	if (ss.fail() || !ss.eof())
	{
		std::cerr << "Error: bad format at: " << date << "\n";
		return false;
	}
	if (sep1 != '-' || sep2 != '-')
	{
		std::cerr << "Error: bad format for separator at: " << date << "\n";
		return false;
	}
	if (m < 1 || m > 12 || d < 1 || d > daysInMonth(y, m))
	{
		std::cerr << "Error: bad value at: " << date << "\n";
		return false;
	}
	return true;
}

bool BitcoinExchange::handleInput(const std::string &filename)
{
	std::ifstream file(filename.c_str()); // input file stream
	std::string line;
	std::string value_str;
	std::string date;
	std::map<std::string, double>::iterator it;
	double value;
	double x;
	double result;

	if (!file.is_open())
	{
		std::cerr << "Error: fail to open " << filename << "\n";
		return false;
	}
	std::getline(file, line);
	while (std::getline(file, line))
	{

		if (!parseLine(line, date, value_str))
			continue;
		if (!isValidDate(date))
			continue;
		if (!isValidValue(value_str, value, line))
			continue;
		it = _data_map.lower_bound(date);
		if (it != _data_map.end() && it->first == date)
		{
			x = it->second;
		}
		else if (it == _data_map.begin())
		{
			std::cerr << "Error: no earlier date registered\n";
			continue;
		}
		else
		{
			--it;
			x = it->second;
		}
		result = x * value;
		std::cout << date << " => " << value << " * " << x << " = " << result << "\n";
		_total_spend += result;
		_btc_owned += value;
	}
	file.close();
	return true;
}

void BitcoinExchange::printMap(std::map<std::string, double> &map)
{
	std::map<std::string, double>::iterator it = map.begin();

	while (it != map.end())
	{
		std::cout << std::setprecision(10);
		std::cout << "Key: " << it->first << " | Value: " << it->second << "\n";
		++it;
	}
}

double BitcoinExchange::getTotalSpend() const
{
	return _total_spend;
}

double BitcoinExchange::getBtcOwned() const
{
	return _btc_owned;
}