#pragma once

#include "Bill.h"
#include "../calculator/CalculatorMaker.h"

int amountFor(const Json::Value& performance, const Json::Value& play)
{
    CalculatorMaker maker(performance, play);
    return maker.getCalculator()->amount();
}

int volumeCreditsFor(const Json::Value& performance, const Json::Value& play) 
{
    CalculatorMaker maker(performance, play);
    return maker.getCalculator()->volumeCredits();
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
