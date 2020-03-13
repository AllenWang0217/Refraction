#pragma once

#include "PerformanceCalculator.h"

struct ComedyCalculator : PerformanceCalculator
{
    ComedyCalculator(const Json::Value& performance, const Json::Value& play) : PerformanceCalculator(performance, play) {};
    int amount()
    {
        int result = 300;
        if (performance["audience"].asInt() > 20) {
            result += 100 + 5 * (performance["audience"].asInt() - 20);
        }
        result += 3 * performance["audience"].asInt();
        return result;
    }
    int volumeCredits() {
        return PerformanceCalculator::volumeCredits() + floor(performance["audience"].asInt() / 5);
    }
};