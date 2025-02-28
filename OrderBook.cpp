#include <bits/stdc++.h>
#include "OrderBook.h"
#include "CSVReader.h"
using namespace std;
OrderBook::OrderBook(string filename)
{
    orders = CSVReader::readCSV(filename);
}
vector<string>OrderBook::getKnownProducts()
{
    vector<string>products;
    map<string,bool>prodMap;
    for (const OrderBookEntry&order:orders)
        prodMap[order.product] = true;
    for (auto const&e:prodMap)products.push_back(e.first);
    return products;
}
vector<OrderBookEntry>OrderBook::getOrders(OrderBookType type, string product, string timestamp)
{
    vector<OrderBookEntry>orders_sub;
    for (OrderBookEntry&order:orders)
    {
        if (order.product == product and order.orderType == type and order.timestamp == timestamp)
            orders_sub.push_back(order);
    }
    return orders_sub;
}
double OrderBook::getHighPrice(vector<OrderBookEntry>&orders)
{
    double maxi = orders[0].price;
    for (const OrderBookEntry&entry: orders)
        maxi = max(maxi,entry.price);
    return maxi;
}
double OrderBook::getLowPrice(vector<OrderBookEntry>&orders)
{
    double mini = orders[0].price;
    for (const OrderBookEntry&entry:orders)
        mini = min(mini,entry.price);
    return mini;
}
string OrderBook::getEarliestTime()
{
    return orders[0].timestamp;
}
string OrderBook::getNextTime(string timestamp)
{
    string nextTimeStamp = "";
    for (OrderBookEntry&entry:orders){
        if (entry.timestamp > timestamp){
            nextTimeStamp = entry.timestamp;
            break;
        }
    }
    if (nextTimeStamp == "")nextTimeStamp = orders[0].timestamp;
    return nextTimeStamp;
}
void OrderBook::insertOrder(OrderBookEntry&order)
{
    orders.push_back(order);
    sort(orders.begin(),orders.end(),OrderBookEntry::compareByTimestamp);
}
vector<OrderBookEntry> OrderBook::match(string product, string timestamp)
{
    vector<OrderBookEntry>sales;
    vector<OrderBookEntry>asks = getOrders(OrderBookType::ask, product, timestamp);
    vector<OrderBookEntry>bids = getOrders(OrderBookType::bid, product, timestamp);
    
    sort(asks.begin(),asks.end(),OrderBookEntry::compareByPriceAscending);
    sort(bids.begin(),bids.end(),OrderBookEntry::compareByPriceDescending);
    
    for (OrderBookEntry&ask : asks){
        for (OrderBookEntry&bid : bids){
            if (bid.price >= ask.price){
                OrderBookType type = OrderBookType::asksale;

                OrderBookEntry sale{ask.price,0,timestamp,product,OrderBookType::asksale};

                if (bid.username == "simuser"){
                    sale.username = "simuser";
                    sale.orderType = OrderBookType::bidsale;
                }
                if (ask.username == "simuser"){
                    sale.username = "simuser";
                    sale.orderType = OrderBookType::asksale;
                }

                sale.amount = min(ask.amount,bid.amount);
                if (sale.amount == 0)continue;
                
                sales.push_back(sale);
                bid.amount -= sale.amount;
                ask.amount -= sale.amount;
                if (ask.amount == 0)break;
            }
        }
    }
    return sales;
}