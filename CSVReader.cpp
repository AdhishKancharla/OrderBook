#include <bits/stdc++.h>
#include "CSVReader.h"
#include "OrderBookEntry.h"
using namespace std;
CSVReader::CSVReader()
{

}
vector<OrderBookEntry> CSVReader::readCSV(string csvfilename)
{
    vector<OrderBookEntry>orders;
    ifstream csvfile{csvfilename};
    string line;
    if (!csvfile.is_open())return orders;
    while (getline(csvfile,line))
    {
        try{
            OrderBookEntry obe = stringsToOBE(tokenise(line,','));
            orders.push_back(obe);
        }
        catch (const exception&e){
            cout<<"Bad Data"<<endl;
            break;
        }
    }
    return orders;
}
vector<string>CSVReader::tokenise(string csvLine, char separator)
{
    vector<string>tokens;
    signed start, end;
    string token;
    start = csvLine.find_first_not_of(separator);
    do{
        end = csvLine.find_first_of(separator,start);
        if (start == csvLine.length() or start == end)break;
        if (end >= 0)token = csvLine.substr(start, end - start);
        else token = csvLine.substr(start, csvLine.length() - start);
        tokens.push_back(token);
        start = end + 1;
    }
    while (end != string::npos);
    return tokens;
}
OrderBookEntry CSVReader::stringsToOBE(vector<string>tokens)
{
    double price, amount;
    if (tokens.size() != 5)
        throw exception{};
    try{
        price = stod(tokens[3]);
        amount = stod(tokens[4]);
    }
    catch(const exception&e)
    {
        cout<<"CSVReader::stringstoOBE Bad float: "<<tokens[3]<<endl;
        cout<<"CSVReader::stringstoOBE Bad float: "<<tokens[4]<<endl;
        throw e;
    }
    OrderBookEntry obe{price,amount,tokens[0],tokens[1],OrderBookEntry::stringToOrder(tokens[2])};
    return obe;
}
OrderBookEntry CSVReader::stringsToOBE(string price, string amount, string timestamp, string product, OrderBookType type)
{
    double p, a;
    try{
        p = stod(price);
        a = stod(amount);
    }
    catch(const exception&e)
    {
        cout<<"CSVReader::stringstoOBE Bad float: "<<price<<endl;
        cout<<"CSVReader::stringstoOBE Bad float: "<<amount<<endl;
    }
    OrderBookEntry obe{p, a, timestamp, product, type};
    return obe;
}