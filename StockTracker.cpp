#include "StockTracker.h"

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <functional>

map<string, int> myStockTickerMap;
map<string, double> myPriceTickerMap;
multimap<double, string> myCapMarketTickerMap;
std::map<double, string>::reverse_iterator rit;

StockTracker::StockTracker() {}

void StockTracker::registerTicker(string tickerSymbol, int sharesOutstanding) {
	myStockTickerMap.insert(std::pair<string, int>(tickerSymbol, sharesOutstanding));
	myPriceTickerMap.insert(std::pair<string, double>(tickerSymbol, 0.0));
}

bool StockTracker::isTicker(string tickerSymbol) {
	return (myStockTickerMap.find(tickerSymbol) != myStockTickerMap.end());
}

int StockTracker::getSharesOutstanding(string tickerSymbol) {
	if (isTicker(tickerSymbol)) {
		return myStockTickerMap[tickerSymbol];
	}
	return 0;
}


void StockTracker::updateCurrentPrice(string tickerSymbol, double price) {
	if (isTicker(tickerSymbol)) {
		myPriceTickerMap[tickerSymbol] = price;
	}

}

double StockTracker::getCurrentPrice(string tickerSymbol) {
	if (isTicker(tickerSymbol)) {
		return myPriceTickerMap[tickerSymbol];
	}
	return 0.0;
}

double StockTracker::getMarketCap(string tickerSymbol) {
	if (isTicker(tickerSymbol)) {
		double mCap = getCurrentPrice(tickerSymbol) * getSharesOutstanding(tickerSymbol);
		myCapMarketTickerMap.insert(std::pair<double, string>((mCap), tickerSymbol));
		return  mCap;
	}
	return 0.0;
}

vector<string> StockTracker::topMarketCaps(int k) {
	vector<string> capMarket;
	int i = 0;
	for (rit = myCapMarketTickerMap.rbegin(); rit != myCapMarketTickerMap.rend() && i < k; ++rit) {
		capMarket.push_back(rit->second);
		i++;
	}

	return capMarket;
}