#pragma once
#include <bits/stdc++.h>
#include "OrderBook.h"
#include "OrderBookEntry.h"
#include "Wallet.h"
using namespace std;
class other
{
    public:
        other();
        /** Call this to start the simulation */
        void init();
    private:
        void invalid();
        void printHelp();
        void printMarketStats();
        void enterAsk();
        void enterBid();
        void printWallet();
        void gotoNext();
        void printMenu();
        void processOption(int userOption);
        int getUserOption();
        string currentTime;
        OrderBook orders{"test.csv"};
        Wallet wallet;
};