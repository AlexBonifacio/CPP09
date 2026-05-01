#pragma once
#include <string>
#include <map>

class BitcoinExchange
{
public:
	BitcoinExchange();

	bool storeData(const std::string &filename);
	bool handleInput(const std::string &filename);
	bool parseLine(std::string &line, std::string &date, std::string &value_str);
	bool isValidDate(const std::string &date) const;
	bool isValidValue(std::string &value_str, double &value, const std::string &str);

	void printMap(std::map<std::string, double> &map);

private:
	std::map<std::string, double> _data_map;
};