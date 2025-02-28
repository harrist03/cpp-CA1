#include "stocks.h"
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>
#include <algorithm>

// Referenced by https://stackoverflow.com/questions/313970/how-to-convert-stdstring-to-lower-case
string toUpper(const string &str)
{
    string result = str;
    transform(result.begin(), result.end(), result.begin(),
              [](unsigned char c)
              { return toupper(c); });
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

// stage 3 q2
void displayStockBasedOnID(vector<Stocks> &stocksList, int stockID)
{
    bool found = false;
    for (Stocks &stock : stocksList)
    {
        if (stock.stockID == stockID)
        {
            displayHeader();
            displayStock(stock);
            cout << string(120, '-');
            found = true;
        }
    }
    if (!found)
    {
        cout << "Stock not found!" << endl;
    }
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
    cout << string(120, '-') << endl;
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

vector<Stocks> displayStocksBasedOnInput(vector<Stocks> &stocksList, string userInput)
{
    vector<Stocks> stocksBasedOnInput;
    bool found = false;
    string upperInput = toUpper(userInput);
    for (vector<Stocks>::iterator it = stocksList.begin(); it != stocksList.end(); it++)
    {
        // create upper case version of stock name
        string upperStockName = toUpper(it->stockName);
        // string::npos is returned if the string is not found
        if (upperStockName.find(upperInput) != string::npos)
        {
            stocksBasedOnInput.push_back(*it);
            found = true;
        }
    }

    if (!found)
    {
        cout << "No stocks found containing " << userInput << endl;
    }
    return stocksBasedOnInput;
}

void displayDescendingStockPrice(vector<Stocks> &stocksList)
{
    // sort the stocksList in descending order of stock price
    sort(stocksList.begin(), stocksList.end(), [](Stocks &a, Stocks &b)
         { return a.stockPrice > b.stockPrice; });
    displayHeader();
    for (Stocks &stock : stocksList)
    {
        displayStock(stock);
    }
    cout << string(120, '-') << endl;
}

void stocks()
{
    vector<Stocks> stocksList;
    populateStocks(stocksList);

    int choice;
    do
    {
        cout << endl
             << string(60, '-') << endl;
        cout << "Stocks Menu" << endl;
        cout << string(60, '-') << endl;
        cout << "1. Display all stocks" << endl;
        cout << "2. Find stock by name" << endl;
        cout << "3. Count stocks by sector" << endl;
        cout << "4. Display stocks by sector" << endl;
        cout << "5. Display highest, lowest PE ratio and average PE ratio" << endl;
        cout << "6. Display stocks based on input" << endl;
        cout << "7. Display stocks in descending order of price" << endl;
        cout << "8. Exit" << endl;
        cout << string(60, '-') << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        cout << endl;
        if (choice == 1)
        {
            displayStocks(stocksList);
        }
        else if (choice == 2)
        {
            string stockName;
            cout << "Enter stock name: ";
            getline(cin, stockName);
            int result = findStocksByName(stocksList, stockName);
            displayStockBasedOnID(stocksList, result);
        }
        else if (choice == 3)
        {
            map<string, int> sectorCount = findCountBySector(stocksList);
            cout << "Stock sector count" << endl;
            for (auto &sector : sectorCount)
            {
                cout << sector.first << ": " << sector.second << endl;
            }
        }
        else if (choice == 4)
        {
            string sectorChoice;
            cout << "Enter stock sector to display: " << endl;
            getline(cin, sectorChoice);
            displayBasedOnUserChoice(stocksList, sectorChoice);
        }
        else if (choice == 5)
        {
            Stocks highestPE, lowestPE;
            int avgPERatio = StocksAveragePERatio(stocksList, highestPE, lowestPE);

            cout << "Highest PE Ratio Stock" << endl;
            displayHeader();
            displayStock(highestPE);
            cout << string(120, '-') << endl;

            cout << "\nLowest PE Ratio Stock" << endl;
            displayHeader();
            displayStock(lowestPE);
            cout << string(120, '-') << endl;

            cout << "\nAverage PE Ratio: " << avgPERatio << endl;
        }
        else if (choice == 6)
        {
            string userInput;
            cout << "Enter a word a stock contains to display: " << endl;
            getline(cin, userInput);
            vector<Stocks> stocksBasedOnInput = displayStocksBasedOnInput(stocksList, userInput);
            displayStocks(stocksBasedOnInput);
        }
        else if (choice == 7)
        {
            displayDescendingStockPrice(stocksList);
        }
        else if (choice == 8)
        {
            cout << "GoodBye!" << endl;
        }
        else
        {
            cout << "Invalid choice! Try again!" << endl;
        }
    } while (choice != 8);
}
