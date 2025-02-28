#include <bits/stdc++.h>
using namespace std;

#include "OrderBookEntry.h"
OrderBookEntry :: OrderBookEntry(double p, double a, string t, string pro, OrderBookType o, string _username):
        price(p), amount(a), timestamp(t), product(pro), orderType(o), username(_username){}

double computeAveragePrice(vector<OrderBookEntry>&entries)
{
    double total = 0;
    for (OrderBookEntry&entry:entries)
        total += entry.price;
        return total/entries.size();
}
double computeLowPrice(vector<OrderBookEntry>&entries)
{
    double low = entries[0].price;
    for (OrderBookEntry&entry:entries)
        low = min(low,entry.price);
        return low;
}
double computeHighPrice(vector<OrderBookEntry>&entries)
{
    double high = entries[0].price;
    for (OrderBookEntry&entry:entries)
        high = max(high,entry.price);
    return high;
}
double computePriceSpread(vector<OrderBookEntry>&entries)
{
    return computeHighPrice(entries) - computeLowPrice(entries);
}
OrderBookType OrderBookEntry::stringToOrder(string a)
{
    if (a == "ask")return OrderBookType::ask;
    if (a == "bid")return OrderBookType::bid;
    return OrderBookType::unknown;
}
bool OrderBookEntry::compareByTimestamp(OrderBookEntry&e1, OrderBookEntry&e2)
{
    return e1.timestamp < e2.timestamp;
}
bool OrderBookEntry::compareByPriceAscending(OrderBookEntry&e1, OrderBookEntry&e2)
{
    return e1.price < e2.price;
}
bool OrderBookEntry::compareByPriceDescending(OrderBookEntry&e1, OrderBookEntry&e2)
{
    return e1.price > e2.price;
}