#pragma once
#include <bits/stdc++.h>
#include "OrderBookEntry.h"
using namespace std;
class CSVReader
{
    public:
        CSVReader();
        static vector<OrderBookEntry> readCSV(string csvfile);
        static vector<string>tokenise(string csvLine, char separator);
        static OrderBookEntry stringsToOBE(string price, string amount, string timestamp, string product, OrderBookType type);
    private:
        static OrderBookEntry stringsToOBE(vector<string>tokens);
};