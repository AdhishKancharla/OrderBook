#pragma once
#include <bits/stdc++.h>
#include "OrderBookEntry.h"
#include "CSVReader.h"
using namespace std;
class Wallet
{
    public:
        Wallet();
        /** Insert currency to wallet */
        bool insertCurrency(string type, double amount);
        /** Check if wallet contains this much currency or more */
        bool containsCurrency(string type, double amount);
        /** Removes currency */
        bool removeCurrency(string type, double amount);
        /** Checks if the wallet can cope with this ask or bid */
        bool canFulfillOrder(OrderBookEntry&order);
        /** Update the contents of the wallet */
        void processSale(OrderBookEntry&sale);
        /** Generate a string representation of the wallet */
        string toString();
        
    private:
        map<string,double>currencies;
};