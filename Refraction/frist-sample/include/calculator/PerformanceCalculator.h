#pragma once
#include "json/json.h"
#include <algorithm>

struct PerformanceCalculator {
    PerformanceCalculator(const Json::Value& performance, const Json::Value& play) : performance(performance), play(play) {};
    virtual ~PerformanceCalculator() {};
    virtual int amount() = 0;
    virtual int volumeCredits(){
        return std::max((performance["audience"].asInt() - 30), 0);
    }
protected:
    const Json::Value& performance;
    const Json::Value& play;
};