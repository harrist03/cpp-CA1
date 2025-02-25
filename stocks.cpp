#include "stocks.h"
#include <fstream>
#include <sstream>
#include <map>

void parse(string line, int &stockID, string &stockSymbol, string &stockName, float &stockPrice, float &stockMarketCap, string &stockSector);

void populateStocks(vector<Stocks> &stocks)
{
    ifstream fin("stocks_data.csv");

    if (fin)
    {
        string line;
        while (!fin.eof())
        {
            int stockID;
            string stockSymbol;
            string stockName;
            float stockPrice;
            float stockMarketCap;
            string stockSector;

            getline(fin, line);
            parse(line, stockID, stockSymbol, stockName, stockPrice, stockMarketCap, stockSector);
            Stocks stock = {stockID, stockSymbol, stockName, stockPrice, stockMarketCap, stockSector};
            stocks.push_back(stock);
        }
    }
    else
    {
        cout << "File not found" << endl;
    }
}

void parse(string line, int &stockID, string &stockSymbol, string &stockName, float &stockPrice, float &stockMarketCap, string &stockSector)
{
    string temp;
    // stringstream object to parse the csv file
    stringstream ss(line);

    // parse stockID
    getline(ss, temp, ',');
    stockID = stoi(temp);
    // parse stockSymbol
    getline(ss, stockSymbol, ',');
    // parse stockName
    getline(ss, stockName, ',');
    // parse stockPrice
    getline(ss, temp, ',');
    // stof converts string to float
    stockPrice = stof(temp);
    // parse stockMarketCap
    getline(ss, temp, ',');
    stockMarketCap = stof(temp);
    // parse stockSector
    getline(ss, stockSector);
}

// stage 3 q1
void displayStocks(vector<Stocks> &stocks)
{
    for (Stocks &stock : stocks)
    {
        cout << "Stock ID: " << stock.stockID << endl;
        cout << "Stock Symbol: " << stock.stockSymbol << endl;
        cout << "Stock Name: " << stock.stockName << endl;
        cout << "Stock Price: $" << stock.stockPrice << endl;
        cout << "Stock Market Cap: $" << stock.stockMarketCap << endl;
        cout << "Stock Sector: " << stock.stockSector << endl;
        cout << endl;
    }
}

// stage 3 q2
int findStocksByName(vector<Stocks> &stocks, string stockName)
{
    for (Stocks &stock : stocks)
    {
        if (stock.stockName.compare(stockName))
        {
            return stock.stockID;
        }
    }
    return -1;
}

// stage 3 q3
map<string, int> findCountBySector(vector<Stocks> &stocks)
{
    map<string, int> sectorCount;
    for (Stocks &stock : stocks)
    {
        sectorCount[stock.stockSector]++;
    }
    return sectorCount;
}

void stocks()
{
    vector<Stocks> stocks;
    populateStocks(stocks);
    // displayStocks(stocks);
    // int result = findStocksByName(stocks, "Apple Inc.");
    // if (result != -1)
    // {
    //     cout << "Stock ID: " << result << endl;
    // }
    // else
    // {
    //     cout << "Stock not found" << endl;
    // }
    map<string, int> sectorCount = findCountBySector(stocks);
    cout << "Stock sector count:" << endl;
    // auto is used to automatically determine the type of the variable
    for (auto &sector : sectorCount)
    {
        cout << sector.first << ": " << sector.second << endl;
    }
}