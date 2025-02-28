#pragma once
#include <bits/stdc++.h>
using namespace std;
enum class OrderBookType{bid, ask, unknown, sale, asksale, bidsale};
class OrderBookEntry{
    public:
        double price;
        double amount;
        string timestamp;
        string product;
        OrderBookType orderType;
        static OrderBookType stringToOrder(string a);
        OrderBookEntry(double p, double a, string t, string pro, OrderBookType o, string username = "dataset");
        static bool compareByTimestamp(OrderBookEntry&e1, OrderBookEntry&e2);
        static bool compareByPriceAscending(OrderBookEntry&e1, OrderBookEntry&e2);
        static bool compareByPriceDescending(OrderBookEntry&e1, OrderBookEntry&e2);
        string username;
};
double computeAveragePrice(vector<OrderBookEntry>&entries);
double computeLowPrice(vector<OrderBookEntry>&entries);
double computeHighPrice(vector<OrderBookEntry>&entries);
double computePriceSpread(vector<OrderBookEntry>&entries);