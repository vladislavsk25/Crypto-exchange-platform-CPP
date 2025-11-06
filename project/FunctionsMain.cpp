#include "FunctionsMain.h"
#include <iostream>
#include <string>
#include "CSVReader.h"
#include <limits>


using namespace std;

FunctionsMain::FunctionsMain(){

}

void FunctionsMain::init(){

    int input;
    currentTime = orderBook.getEarliestTime();

    wallet.insertCurrency("BTC", 10);

    while (true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}


void FunctionsMain::printMenu()
{

    cout << "1: Print help " << endl;
    cout << "2: Print exchange stats " << endl;
    cout << "3: Make an ask " << endl;
    cout << "4: Make a bid " << endl;
    cout << "5: Print wallet " << endl;
    cout << "6: Continue " << endl;

    cout << "================" << endl;

    cout << "Current time is: " << currentTime << endl;
}

void FunctionsMain::printHelp()
{
    cout << "Help - your aim is to make money. Analyse the market and make bids and offers " << endl;
}

void FunctionsMain::printMarketStats()
{
    for (string const& p: orderBook.getKnownProducts()){
        cout << "Product: " << p << endl;
        vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);

        cout << "Asks seen: " << entries.size() << endl;

        cout << "Max ask: " << OrderBook::getHighPrice(entries) << endl;
        cout << "Min ask: " << OrderBook::getLowPrice(entries) << endl;

        cout << "Average price: " << OrderBook::getAveragePrice(entries) << endl;
    }

}

void FunctionsMain::enterAsk()
{
    cout << "Make an ask - enter the amount: product, price, amount, eg ETH/BTC, 200, 0.5" << endl;
    string input;
    getline(cin, input);

    vector<string> tokens = CSVReader::tokenise(input, ',');
    if(tokens.size() != 3){
        cout << "FunctionsMain::enterAsk Bad input! " << input << endl;
    } else {
        try{
        OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1],
                                                     tokens[2],
                                                     currentTime,
                                                     tokens[0],
                                                     OrderBookType::ask);
        obe.username = "simuser";
        if (wallet.canFulfillOrder(obe))
        {
            cout << "Wallet looks good. " << endl;
            orderBook.insertOrder(obe);
            } else {
                cout << "Wallet has insufficient funds. " << endl;
            }
        } catch(const exception& e){
            cout << "FunctionsMain::enterAsk Bad input" << endl;
        }
    }

    cout << "You typed: " << input << endl;
}

void FunctionsMain::enterBid()
{
    cout << "Make a bid - enter the amount: product, price, amount, eg ETH/BTC, 200, 0.5" << endl;
    string input;
    getline(cin, input);

    vector<string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        cout << "FunctionsMain::enterBid Bad input! " << input << endl;
    }
    else
    {
        try
        {
            OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1],
                                                         tokens[2],
                                                         currentTime,
                                                         tokens[0],
                                                         OrderBookType::bid);
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                cout << "Wallet looks good. " << endl;
                orderBook.insertOrder(obe);
            }
            else
            {
                cout << "Wallet has insufficient funds. " << endl;
            }
        }
        catch (const exception &e)
        {
            cout << "FunctionsMain::enterBid Bad input" << endl;
        }
    }

    cout << "You typed: " << input << endl;
}

void FunctionsMain::printWallet()
{
    cout << wallet.toString() << endl;
}

void FunctionsMain::gotoNexttimeFrame()
{
    cout << "Going to next time frame " << endl;
    vector<OrderBookEntry> sales = orderBook.matchAsksToBids("ETH/BTC", currentTime);
    cout << "Sales: " << sales.size() << endl;
    for (OrderBookEntry& sale : sales)
    {
        cout << "Sale price: " << sale.price << " amount " << sale.amount << endl;
        if(sale.username == "simuser"){
            wallet.processSale(sale);
        }
    }
    currentTime = orderBook.getNextTime(currentTime);
}

int FunctionsMain::getUserOption()
{

    int userOption = 0;
    string line;
    cout << "Type in 1-6" << endl;
    getline(cin, line);

    try{
    userOption = stoi(line);
    } catch(const exception& e){
        cout << "FunctionsMain::getUserOption Bad input" << endl;
    }
    cout << "You choose: " << userOption << endl;
    return userOption;
}

void FunctionsMain::processUserOption(int userOption)
{
    if (userOption == 0)
    {
        cout << "Invalid choice. Choose 1-6 " << endl;
    }

    if (userOption == 1)
    {
        printHelp();
    }

    if (userOption == 2)
    {
        printMarketStats();
    }

    if (userOption == 3)
    {
        enterAsk();
    }

    if (userOption == 4)
    {
        enterBid();
    }

    if (userOption == 5)
    {
        printWallet();
    }

    if (userOption == 6)
    {
        gotoNexttimeFrame();
    }
}