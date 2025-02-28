#include "Wallet.h"
#include <bits/stdc++.h>
using namespace std;
Wallet::Wallet()
{

}
bool Wallet::insertCurrency(string type, double amount)
{
    if (amount < 0)return false;
    currencies[type] += amount;
    return true;
}
bool Wallet::removeCurrency(string type, double amount)
{
    if (amount < 0 or !containsCurrency(type,amount))return false;
    currencies[type] -= amount;
    return true;
}
bool Wallet::containsCurrency(string type, double amount)
{
    return currencies[type] >= amount;
}
string Wallet::toString()
{
    string s;
    for (const pair<string,double>&currency:currencies){
        string denomination = currency.first;
        double amount = currency.second;
        s += denomination + ": " + to_string(amount) + "\n";
    }
    return s;
}
bool Wallet::canFulfillOrder(OrderBookEntry&order)
{
    vector<string>currs = CSVReader::tokenise(order.product,'/');
    if (order.orderType == OrderBookType::ask)
    {
        double amount = order.amount;
        string currency = currs[0];
        return containsCurrency(currency,amount);
    }
    else if (order.orderType == OrderBookType::bid)
    {
        double amount = order.amount * order.price;
        string currency = currs[1];
        return containsCurrency(currency,amount);
    }
    return false;
}
void Wallet::processSale(OrderBookEntry&sale)
{
    vector<string>currs = CSVReader::tokenise(sale.product,'/');
    double incomingAmount = sale.amount;
    string incomingCurrency = currs[0];
    double outgoingAmount = sale.amount * sale.price;
    string outgoingCurrency = currs[1];
    if (sale.orderType == OrderBookType::asksale)
    {
        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
    else if (sale.orderType == OrderBookType::bidsale)
    {
        currencies[incomingCurrency] -= incomingAmount;
        currencies[outgoingCurrency] += outgoingAmount;
    }
}