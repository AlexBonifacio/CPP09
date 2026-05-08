
#include "BitcoinValue.hpp"

#include <curl/curl.h>
#include <string>
#include <iostream>
#include <cstdlib> // stdtod
#include <iomanip> // setprecision

#include <exception>

BitcoinValue::BitcoinValue(double total_spend, double btc_owned) : _total_spend(total_spend), _btc_owned(btc_owned)
{
	curlBitcoin();
}

BitcoinValue::~BitcoinValue()
{
}

// contents points to datas, size = char size (mostly), chunk = total size received
static size_t write_callback(void *contents, size_t size,
							 size_t chunk, std::string *output)
{
	size_t total;

	total = size * chunk;
	output->append((char *)contents, total);
	return (total);
}

bool BitcoinValue::extractValue(const std::string &input)
{
	std::string key;
	std::string s_value;
	size_t start;
	size_t end;
	double d_value;

	if (input.find("symbol") == std::string::npos || input.find("price") == std::string::npos)
		return false;
	start = input.find(":");
	if (start == std::string::npos)
	{
		return false;
	}
	start += 2;

	end = input.find("\"", start);
	if (start == std::string::npos)
		return false;
	key = input.substr(start, end - start);

	start = input.find(":", end);
	if (start == std::string::npos)
		return false;
	start += 2;

	end = input.find("\"", start);
	if (start == std::string::npos)
		return false;
	s_value = input.substr(start, end - start);
	d_value = strtod(s_value.c_str(), NULL);
	_pmap[key] = d_value;

	std::map<std::string, double>::iterator it = _pmap.begin();
	std::cout << "Value for " << it->first << " today is " << std::fixed << std::setprecision(2) << it->second << "\n";
	std::cout << "You bought for a total of " << _total_spend << " euros of " << it->first << "\n";
	std::cout << "You now own a total of: " << _btc_owned << "BTC for a total amount of: " << it->second * _btc_owned << "\n";
	return true;
}

void BitcoinValue::curlBitcoin(void)
{
	CURL *curl;
	CURLcode res;
	std::string response;

	curl = curl_easy_init();
	if (!curl)
		throw std::runtime_error("Error: curl init failed");

	curl_easy_setopt(curl, CURLOPT_URL,
					 "https://api.binance.com/api/v3/ticker/price?symbol=BTCEUR");
	// curl_easy_setopt(curl, CURLOPT_USERAGENT,
	// 				 "curl_tests");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

	res = curl_easy_perform(curl);

	if (res != CURLE_OK)
	{
		throw std::runtime_error("Error: curl");
	}
	// else
	// 	std::cout << "Curl response:\n" << response << std::endl;

	curl_easy_cleanup(curl);
	if (!extractValue(response))
	{
		throw std::runtime_error("Error: curl response invalid");
	}
}