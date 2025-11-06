#pragma once 

#include "OrderBookEntry.h"
#include <vector>
#include <string>



class CSVReader{

    public:
        CSVReader();

        static std::vector<OrderBookEntry> readCSV(std::string csvfile);
        static std::vector<std::string> tokenise(std::string cvsLine, char separator);
        static OrderBookEntry stringsToOBE(string price, string amount, string timestamp, string product, OrderBookType OrderBookType);

    private:
        static OrderBookEntry stringsToOBE(std::vector<std::string> strings);
};