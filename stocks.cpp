#include "stocks.h"
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>

void populateStocks(vector<Stocks> &stocksList)
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
            stocksList.push_back(stock);
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

// Display header for the table
void displayHeader()
{
    cout << string(113, '-') << endl;
    cout << left
         << setw(5) << "ID"
         << setw(40) << "Name"
         << setw(8) << "Symbol"
         << right
         << setw(12) << "Price"
         << setw(20) << "Market Cap ($B)"
         << setw(11) << "  Sector" << endl;
    cout << string(113, '-') << endl;
}

// Display a single stock in a formatted way
void displayStock(Stocks &stock)
{
    // convert market cap to billions for readability
    double marketCapBillions = stock.stockMarketCap / 1000000000.0;

    // Format price and market cap as strings with $ symbol
    stringstream priceStr, marketCapStr;
    // combine "$ + price" to string
    priceStr << "$" << fixed << setprecision(2) << stock.stockPrice;
    marketCapStr << "$" << fixed << setprecision(0) << marketCapBillions << "B";

    cout << left
         << setw(5) << stock.stockID
         << setw(40) << stock.stockName
         << setw(8) << stock.stockSymbol
         << right
         << setw(13) << priceStr.str()
         << setw(13) << marketCapStr.str()
         << setw(11) << "  " << stock.stockSector
         << endl;
}

// stage 3 q1
void displayStocks(vector<Stocks> &stocksList)
{
    displayHeader();
    for (Stocks &stock : stocksList)
    {
        displayStock(stock);
    }
    cout << string(113, '-') << endl;
}

// stage 3 q2
int findStocksByName(vector<Stocks> &stocksList, string stockName)
{
    for (Stocks &stock : stocksList)
    {
        if (stock.stockName == stockName)
        {
            return stock.stockID;
        }
    }
    return -1;
}

// stage 3 q3
map<string, int> findCountBySector(vector<Stocks> &stocksList)
{
    map<string, int> sectorCount;
    for (Stocks &stock : stocksList)
    {
        sectorCount[stock.stockSector]++;
    }
    return sectorCount;
}

// stage 3 q4
void displayBasedOnUserChoice(vector<Stocks> &stocksList, string choice)
{
    bool found = false;
    displayHeader();
    for (Stocks &stock : stocksList)
    {
        if (stock.stockSector == choice)
        {
            displayStock(stock);
            found = true;
        }
    }
    if (!found)
    {
        cout << "No stocks found in the " << choice << " sector." << endl;
    }
    else
    {
        cout << string(113, '-') << endl;
    }
}

void stocks()
{
    vector<Stocks> stocksList;
    populateStocks(stocksList);
    // // stage 3 q1
    // displayStocks(stocksList);
    // // stage 3 q2
    // int result = findStocksByName(stocks, "Apple Inc.");
    // if (result != -1)
    // {
    //     cout << "Stock ID: " << result << endl;
    // }
    // else
    // {
    //     cout << "Stock not found" << endl;
    // }
    // // stage 3 q3
    // map<string, int> sectorCount = findCountBySector(stocksList);
    // cout << "Stock sector count:" << endl;
    // // auto is used to automatically determine the type of the variable
    // for (auto &sector : sectorCount)
    // {
    //     cout << sector.first << ": " << sector.second << endl;
    // }
    // stage 3 q4
    string sectorChoice;
    cout << "Enter stock sector to display (Must have a capital letter at the begining!): " << endl;
    getline(cin, sectorChoice);
    displayBasedOnUserChoice(stocksList, sectorChoice);
}