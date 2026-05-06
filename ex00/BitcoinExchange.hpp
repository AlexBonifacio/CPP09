#pragma once
#include <string>
#include <map>

class BitcoinExchange
{
public:
	BitcoinExchange(const std::string& datas, const std::string& invest);
	~BitcoinExchange();

	bool storeData(const std::string &filename);
	bool handleInput(const std::string &filename);
	bool parseLine(std::string &line, std::string &date, std::string &value_str);
	bool isValidDate(const std::string &date) const;
	bool isValidValue(std::string &value_str, double &value, const std::string &str);

	double getTotalSpend() const;
	double getBtcOwned() const;

	void printMap(std::map<std::string, double> &map);


private:
	BitcoinExchange();
	std::map<std::string, double> _data_map;
	BitcoinExchange(const BitcoinExchange& copy);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	double _total_spend;
	double _btc_owned;
};