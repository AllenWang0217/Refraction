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
    cout << "========" << "print statement" << "========" << endl;
    cout << "Statement for : " << bill.customer.c_str() << endl;
    for (int i = 0; i < bill.plays.size(); i++)
    {
        Play& play = bill.plays[i];
        printf("    %s: %d (%d seats)\n", play.name.c_str(), play.cost, play.seats);
    }
    printf("Amount owed is %d\n", bill.total);
    printf("You earned %d credits\n", bill.credit);
}

int amountFor(const Json::Value& performance, const Json::Value& play)
{
    int result = 0;
    if (!strcmp(play["type"].asString().c_str(), "tragedy"))
    {
        result = 400;
        if (performance["audience"].asInt() > 30) {
            result += 10 * (performance["audience"].asInt() - 30);
        }
    }
    else if (!strcmp(play["type"].asString().c_str(), "comedy"))
    {
        result = 300;
        if (performance["audience"].asInt() > 20) {
            result += 100 + 5 * (performance["audience"].asInt() - 20);
        }
        result += 3 * performance["audience"].asInt();
    }
    else
    {
        throw "unknow type";
    }
    return result;
}

int volumeCreditsFor(const Json::Value& performance, const Json::Value& play) {
    int result = 0;
    result += max((performance["audience"].asInt() - 30), 0);
    // add extra credit for every ten comedy attendees
    if ("comedy" == play["type"].asString()) result += floor(performance["audience"].asInt() / 5);
    return result;
}

#define PLAY plays[perf["playID"].asString()]

int totalAmount(Json::Value& invoice, Json::Value& plays)
{
    int result = 0;
    for (Json::Value& perf : invoice["performances"]) {
        result += amountFor(perf, PLAY);
    }
    return result;
}
int totalVolumeCredits(Json::Value& invoice, Json::Value& plays)
{
    int result = 0;
    for (Json::Value& perf : invoice["performances"]) {
        result += volumeCreditsFor(perf, PLAY);
    }
    return result;
}

Bill statement(Json::Value& invoice, Json::Value& plays)
{
    Bill bill(invoice["customer"].asString());
    for (Json::Value& perf : invoice["performances"]) {
        Play playPay(PLAY["name"].asString(), amountFor(perf, PLAY), perf["audience"].asInt());
        bill.plays.push_back(playPay);
    }
    bill.total = totalAmount(invoice, plays);
    bill.credit = totalVolumeCredits(invoice, plays);
    return bill;
}
