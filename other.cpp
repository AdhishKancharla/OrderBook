#include <bits/stdc++.h>
#include "other.h"
#include "OrderBookEntry.h"
#include "CSVReader.h"
using namespace std;
other::other()
{

}
void other::init()
{
    int input;
    currentTime = orders.getEarliestTime();
    wallet.insertCurrency("BTC",10);
    while (true){
        printMenu();
        input = getUserOption();
        if (input == 7)break;
        processOption(input);
    }
}
void other::invalid()
{
    cout<<"Invalid choice. Choose 1-6"<<endl<<endl;
}
void other::printHelp()
{
    cout<<"Your aim is to make money. Analyse the market and make bids and offers."<<endl<<endl;
}
void other::printMarketStats()
{
    vector<string>products = orders.getKnownProducts();
    for (const string&s:products){
        cout<<"Product: "<<s<<endl;
        vector<OrderBookEntry>entries = orders.getOrders(OrderBookType::ask, s, currentTime);
        cout<<"Asks for "<<s<<": "<<entries.size()<<endl;
        cout<<"Maximum ask: "<<OrderBook::getHighPrice(entries)<<endl;
        cout<<"Minimum ask: "<<OrderBook::getLowPrice(entries)<<endl;
    }
}
void other::enterAsk()
{
    cout<<"Make an ask - enter the amount at which you wish to sell: Product, Price, Amount"<<endl<<endl;
    string input;
    getline(cin,input);
    getline(cin,input);
    vector<string>tokens = CSVReader::tokenise(input,',');
    if (tokens.size() != 3){
        cout<<"Bad Input"<<endl;
    }
    else{
        try{
            OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::ask);
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe)){
                orders.insertOrder(obe);
                cout<<"Wallet looks good"<<endl;
            }
            else
                cout<<"Insufficient funds"<<endl;
        }
        catch (const exception&e){
            cout<<"Other::enterAsk Bad Input: "<<input<<endl;
        }
    }
}
void other::enterBid()
{
    cout<<"Make a bid - enter the amount at which you wish to buy: Product, Price, Amount"<<endl<<endl;
    string input;
    getline(cin,input);
    getline(cin,input);
    vector<string>tokens = CSVReader::tokenise(input,',');
    if (tokens.size() != 3){
        cout<<"Bad Input"<<endl;
    }
    else{
        try{
            OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::bid);
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe)){
                orders.insertOrder(obe);
                cout<<"Wallet looks good"<<endl;
            }
            else
                cout<<"Insufficient funds"<<endl;
        }
        catch (const exception&e){
            cout<<"Other::enterBid Bad Input: "<<input<<endl;
        }
    }
}
void other::printWallet()
{
    cout<<"Your wallet: "<<wallet.toString()<<endl<<endl;
}
void other::gotoNext()
{
    cout<<"Going to next timeframe"<<endl;
    vector<OrderBookEntry>sales = orders.match("ETH/BTC",currentTime);
    cout<<"There have been "<<sales.size()<<endl;
    for (OrderBookEntry&sale:sales){
        cout<<"Sale price: "<<sale.price<<" Sale amount: "<<sale.amount<<endl;
        if (sale.username == "simuser")wallet.processSale(sale);
    }
    cout<<endl;
    currentTime = orders.getNextTime(currentTime);
}
void other::printMenu()
{
    cout<<"1: Print help"<<endl;
    cout<<"2: Print exchange stats"<<endl;
    cout<<"3: Make an ask"<<endl;
    cout<<"4: Make a bid"<<endl;
    cout<<"5: Print wallet"<<endl;
    cout<<"6: Continue"<<endl;
    cout<<"7: Exit"<<endl;

    cout<<"============="<<endl;
    cout<<"Current Time is: "<<currentTime<<endl;
    cout<<"Type in 1-7: ";
}
int other::getUserOption()
{
    int userOption;
    cin>>userOption;
    cout<<"You chose: "<<userOption<<endl<<endl;
    return userOption;
}
void other::processOption(int userOption)
{
    switch (userOption){
        case 0:
            invalid();
            break;
        case 1:
            printHelp();
            break;
        case 2:
            printMarketStats();
            break;
        case 3:
            enterAsk();
            break;
        case 4:
            enterBid();
            break;
        case 5:
            printWallet();
            break;
        case 6:
            gotoNext();
            break;
    }
}