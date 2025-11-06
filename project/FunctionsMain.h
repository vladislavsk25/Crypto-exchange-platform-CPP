#pragma once 
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"

class FunctionsMain{

    public:
        FunctionsMain();
        /** Use this functio to start simulation*/
        void init();

    private:
        /** Use this fucntion to print out menu*/
        void printMenu();
        void printHelp();
        void printMarketStats();
        void enterAsk();
        void enterBid();
        void printWallet();
        void gotoNexttimeFrame();
        int getUserOption();
        void processUserOption(int userOption);

        std::string currentTime;

        OrderBook orderBook{"20200317.csv"};

        Wallet wallet;
};