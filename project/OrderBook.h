#pragma once 
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <vector>
#include <string>

using namespace std;

class OrderBook{


    public:
    /** Construct, reading a data from csv file */
        OrderBook(string filename);
    /** return a vector of all known products in the dataset */
        vector<string> getKnownProducts();
    /** return vector of orders taking into account sent filters */
        vector<OrderBookEntry> getOrders(OrderBookType type,
                                 string product,
                                 string timestamp);

        /** returns the earliest time in the orderbook*/
        string getEarliestTime();
        /** returns the next time after the sent time in the orderbook 
         * If there is no next timestamp, wraps around to the start*/
        string getNextTime(string timestamp);

        void insertOrder(OrderBookEntry& order);

        vector<OrderBookEntry> matchAsksToBids(string product, string timestamp);

        static double getHighPrice(vector<OrderBookEntry> &orders);
        static double getLowPrice(vector<OrderBookEntry> &orders);
        static double getAveragePrice(vector<OrderBookEntry> &orders);

    private:
        vector<OrderBookEntry> orders;
};