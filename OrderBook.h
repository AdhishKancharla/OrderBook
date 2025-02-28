#pragma once
#include <bits/stdc++.h>
#include "CSVReader.h"
#include "OrderBookEntry.h"
using namespace std;
class OrderBook{
    public:
    /** construct by reading a CSV data-file */
        OrderBook(string filename);
    /** vector of all known products in the data-set */
        vector<string>getKnownProducts();
    /** vector of all products according to given specifications */
        vector<OrderBookEntry>getOrders(OrderBookType type, string product, string timestamp);
        static double getHighPrice(vector<OrderBookEntry>&orders);
        static double getLowPrice(vector<OrderBookEntry>&orders);
    /** returns the earliest time in the orderbook */
        string getEarliestTime();
    /** returns the next time after a timestamp in the orderbook
     * if there is no next timestamp wraps around to the start
     */
        string getNextTime(string timestamp);
    /** */
        vector<OrderBookEntry>match(string product, string timestamp);
        void insertOrder(OrderBookEntry&order);
    private:
        vector<OrderBookEntry>orders;
};