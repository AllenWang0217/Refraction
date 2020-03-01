#include "../../include/json-reader/JsonReader.h"
#include <fstream>
#include <iostream>

using namespace std;

void printInvoices(Json::Value& root)
{
    cout << "========" << "invoices.json" << "========" << endl;
    cout << "customer: " << root["customer"].asString() << endl;
    cout << "performances:" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "  {" << "playID:" << root["performances"][i]["playID"].asString() << "; ";
        cout << "   " << "audience:" << root["performances"][i]["audience"].asInt() << "}," << endl;
    }
}

void printPlays(Json::Value& root)
{
    cout << "========" << "plays.json" << "========" << endl;
    cout << "hamlet: {name: " << root["hamlet"]["name"].asString() << ", type:" << root["hamlet"]["type"].asString() << "}," << endl;
    cout << "as-like: {name: " << root["as-like"]["name"].asString() << ", type:" << root["as-like"]["type"].asString() << "}," << endl;
    cout << "othello: {name: " << root["othello"]["name"].asString() << ", type:" << root["othello"]["type"].asString() << "}" << endl;
}

bool jsonReader(string& path, Json::Value& root)
{
    ifstream is(path, ios::binary);
    if (!is.is_open())
    {
        cout << "open json file failed." << endl;
        return false;
    }

    JSONCPP_STRING errs;
    Json::CharReaderBuilder readerBuilder;

    bool result = Json::parseFromStream(readerBuilder, is, &root, &errs);
    if (!result || !errs.empty()) {
        cout << "parseJson err. " << errs << endl;
        is.close();
        return false;
    }
    is.close();
    return true;
}