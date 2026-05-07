
#include <string>
#include <map>
class BitcoinValue
{
public:
	BitcoinValue(double total_spend, double btc_owned);
	~BitcoinValue();
	void curlBitcoin();

private:
	double _btc_val;
	double _total_spend;
	double _btc_owned;

	std::map<std::string, double> _pmap;
	bool extractValue(const std::string &input);
	void valueToday();
	BitcoinValue();
	BitcoinValue(const BitcoinValue &copy);
	BitcoinValue &operator=(const BitcoinValue &other);

};