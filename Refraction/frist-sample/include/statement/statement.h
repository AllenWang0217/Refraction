#pragma once

#include "json/json.h"
#include "Bill.h"
#include <algorithm>

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

int totalAmount(const Json::Value& invoice, const Json::Value& plays)
{
    int result = 0;
    for (const Json::Value& perf : invoice["performances"]) {
        result += amountFor(perf, PLAY);
    }
    return result;
}
int totalVolumeCredits(const Json::Value& invoice, const  Json::Value& plays)
{
    int result = 0;
    for (const Json::Value& perf : invoice["performances"]) {
        result += volumeCreditsFor(perf, PLAY);
    }
    return result;
}

Bill statement(const Json::Value& invoice, const Json::Value& plays)
{
    Bill bill(invoice["customer"].asString());
    for (const Json::Value& perf : invoice["performances"]) {
        Play play(PLAY["name"].asString(), amountFor(perf, PLAY), perf["audience"].asInt());
        bill.plays.push_back(play);
    }
    bill.total = totalAmount(invoice, plays);
    bill.credit = totalVolumeCredits(invoice, plays);
    return bill;
}
