#include <iostream>
#include <vector>
using namespace std;

struct Stocks
{
    int stockID;
    string stockName;
    string stockSymbol;
    float stockPrice;
    float stockMarketCap;
    string stockSector;
};

void stocks();
void parse(string line, int &stockID, string &stockName, string &stockSymbol, float &stockPrice, float &stockMarketCap, string &stockSector);
void displayStocks(const vector<Stocks> &stocks);