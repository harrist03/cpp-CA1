#include "stocks.h"
#include <fstream>
#include <sstream>

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

void displayStocks(Stocks &stock)
{
    cout << "Stock ID: " << stock.stockID << endl;
    cout << "Stock Symbol: " << stock.stockSymbol << endl;
    cout << "Stock Name: " << stock.stockName << endl;
    cout << "Stock Price: $" << stock.stockPrice << endl;
    cout << "Stock Market Cap: $" << stock.stockMarketCap << endl;
    cout << "Stock Sector: " << stock.stockSector << endl;
    cout << endl;
}

void stocks()
{
    vector<Stocks> stocks;
    populateStocks(stocks);
    for (Stocks &stock : stocks)
    {
        displayStocks(stock);
    }
}