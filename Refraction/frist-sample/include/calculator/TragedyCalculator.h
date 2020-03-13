#pragma once

#include "PerformanceCalculator.h"

struct TragedyCalculator : PerformanceCalculator
{
    TragedyCalculator(const Json::Value& performance, const Json::Value& play) : PerformanceCalculator(performance, play) {};
    int amount()
    {
        int result = 400;
        if (performance["audience"].asInt() > 30) {
            result += 10 * (performance["audience"].asInt() - 30);
        }
        return result;
    }
};