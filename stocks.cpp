#include "stocks.h"
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>
#include <algorithm>

// Referenced by https://stackoverflow.com/questions/313970/how-to-convert-stdstring-to-lower-case
string toUpper(const string &str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), 
              [](unsigned char c){ return toupper(c); });
    return result;
}

void parse(string line, int &stockID, string &stockSymbol, string &stockName, float &stockPrice, float &stockMarketCap, string &stockSector, int &stockPERatio)
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
    getline(ss, temp, ',');
    stockSector = temp;
    // parse stockPERatio
    getline(ss, temp);
    stockPERatio = stoi(temp);
}

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
            int stockPERatio;

            getline(fin, line);
            parse(line, stockID, stockSymbol, stockName, stockPrice, stockMarketCap, stockSector, stockPERatio);
            Stocks stock = {stockID, stockSymbol, stockName, stockPrice, stockMarketCap, stockSector, stockPERatio};
            stocksList.push_back(stock);
        }
    }
    else
    {
        cout << "File not found" << endl;
    }
}

// Display header for the table
void displayHeader()
{
    cout << string(120, '-') << endl;
    cout << left
         << setw(5) << "ID"
         << setw(40) << "Name"
         << setw(8) << "Symbol"
        //  << right
         << setw(12) << "Price"
         << setw(15) << "MarketCap($B)"
         << left
         << setw(25) << "  Sector"
         << setw(25) << "PE Ratio" << endl;
    cout << string(120, '-') << endl;
}

// Display a single stock in a formatted way
void displayStock(Stocks &stock)
{
    // convert market cap to billions for readability
    double marketCapBillions = stock.stockMarketCap / 1000000000.0;

    // Format price and market cap as strings with $ symbol
    stringstream priceStr, marketCapStr;
    priceStr << "$" << fixed << setprecision(2) << stock.stockPrice;
    marketCapStr << "$" << fixed << setprecision(2) << marketCapBillions << "B";

    cout << left
         << setw(5) << stock.stockID
         << setw(40) << stock.stockName
         << setw(8) << stock.stockSymbol
        //  << right
         << setw(12) << priceStr.str()
         << setw(15) << marketCapStr.str()
         << left
         << "  " << setw(22) << stock.stockSector
         << "  " << setw(22) << stock.stockPERatio << endl;
}

// stage 3 q1
void displayStocks(vector<Stocks> &stocksList)
{
    displayHeader();
    for (Stocks &stock : stocksList)
    {
        displayStock(stock);
    }
    cout << string(120, '-') << endl;
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
        if (toUpper(stock.stockSector) == toUpper(choice))
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
        cout << string(120, '-') << endl;
    }
}

int StocksAveragePERatio(vector<Stocks> &stocksList, Stocks &highest, Stocks &lowest)
{
    highest = stocksList[0];
    lowest = stocksList[0];
    double totalPERatio = 0;

    for (const Stocks &stock : stocksList)
    {
        if (highest.stockPERatio < stock.stockPERatio)
        {
            highest = stock;
        }
        if (lowest.stockPERatio > stock.stockPERatio)
        {
            lowest = stock;
        }
        totalPERatio += stock.stockPERatio;
    }
    int avgPERatio = totalPERatio / stocksList.size();

    return avgPERatio;
}

void stocks()
{
    vector<Stocks> stocksList;
    populateStocks(stocksList);
    // stage 3 q1
    // displayStocks(stocksList);

    // stage 3 q2
    // int result = findStocksByName(stocks, "Apple Inc.");
    // if (result != -1)
    // {
    //     cout << "Stock ID: " << result << endl;
    // }
    // else
    // {
    //     cout << "Stock not found" << endl;
    // }

    // stage 3 q3
    // map<string, int> sectorCount = findCountBySector(stocksList);
    // cout << "Stock sector count:" << endl;
    // // auto is used to automatically determine the type of the variable
    // for (auto &sector : sectorCount)
    // {
    //     cout << sector.first << ": " << sector.second << endl;
    // }
     
    // stage 3 q4
    // string sectorChoice;
    // cout << "Enter stock sector to display: " << endl;
    // getline(cin, sectorChoice);
    // displayBasedOnUserChoice(stocksList, sectorChoice);

    // stage 3 q5
    // Stocks highestPE, lowestPE;
    // int avgPERatio = StocksAveragePERatio(stocksList, highestPE, lowestPE);

    // cout << "Highest PE Ratio Stock" << endl;
    // displayHeader();
    // displayStock(highestPE);
    // cout << string(120, '-') << endl;

    // cout << "\nLowest PE Ratio Stock" << endl;
    // displayHeader();
    // displayStock(lowestPE);
    // cout << string(120, '-') << endl;

    // cout << "\nAverage PE Ratio: " << avgPERatio << endl;
}