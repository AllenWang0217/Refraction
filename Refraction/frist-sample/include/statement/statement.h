#pragma once

#include "json/json.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Play {
    Play(string name, int cost, int seats) : name(name), cost(cost), seats(seats) {};
    string name;
    int cost;
    int seats;
};
struct Bill {
    Bill() {};
    Bill(string customer) : customer(customer), total(0), credit(0) {};
    string customer;
    vector<Play> plays;
    int total;
    int credit;
};

void printBill(Bill& bill)
{
    cout << "\n========" << "print statement" << "========" << endl;
    cout << "Statement for : " << bill.customer.c_str() << endl;
    for (int i = 0; i < bill.plays.size(); i++)
    {
        Play& play = bill.plays[i];
        printf("    %s: %d (%d seats)\n", play.name.c_str(), play.cost, play.seats);
    }
    printf("Amount owed is %d\n", bill.total);
    printf("You earned %d credits\n", bill.credit);
}

Bill statement(Json::Value& invoice, Json::Value& plays)
{
    int totalAmount = 0;
    int volumeCredits = 0;
    Bill bill(invoice["customer"].asString());

    for (Json::Value& perf : invoice["performances"]) {
        Json::Value& play = plays[perf["playID"].asString()];
        int thisAmount = 0;
        if (!strcmp(play["type"].asString().c_str(), "tragedy"))
        {
            thisAmount = 400;
            if (perf["audience"].asInt() > 30) {
                thisAmount += 10 * (perf["audience"].asInt() - 30);
            }
        }
        else if (!strcmp(play["type"].asString().c_str(), "comedy"))
        {
            thisAmount = 300;
            if (perf["audience"].asInt() > 20) {
                thisAmount += 100 + 5 * (perf["audience"].asInt() - 20);
            }
            thisAmount += 3 * perf["audience"].asInt();
        }
        else
        {
            cout << "ERROR" << endl;;
        }

        // add volume credits
        volumeCredits += max((perf["audience"].asInt() -  30), 0);
        // add extra credit for every ten comedy attendees
        if ("comedy" ==  play["type"].asString()) volumeCredits += floor(perf["audience"].asInt()/5);
        // print line for this order
        totalAmount += thisAmount;
        Play playPay(play["name"].asString(), thisAmount, perf["audience"].asInt());
        bill.plays.push_back(playPay);
    }
    bill.total = totalAmount;
    bill.credit = volumeCredits;

    return bill;
}
