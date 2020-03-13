#pragma once

#include "ComedyCalculator.h"
#include "TragedyCalculator.h"
#include <string>

using std::string;

struct CalculatorMaker {
    CalculatorMaker(const Json::Value& performance, const Json::Value& play)
    {
        if (!strcmp(play["type"].asString().c_str(), "tragedy"))
        {
            calculator = new TragedyCalculator(performance, play);
        }
        else if (!strcmp(play["type"].asString().c_str(), "comedy"))
        {
            calculator = new ComedyCalculator(performance, play);
        }
        else
        {
            throw "unknow type";
        }
    }
    ~CalculatorMaker() { delete calculator; calculator = NULL; }

    PerformanceCalculator* getCalculator() { return calculator; }
private:
    PerformanceCalculator* calculator;
};