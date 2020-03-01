#pragma once

#include "json/json.h"
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

void statement(Json::Value& invoice, Json::Value& plays)
{
    cout << "\n========" << "print statement" << "========" << endl;
    int totalAmount = 0;
    int volumeCredits = 0;
    cout << "Statement for : " << invoice["customer"].asString() << endl;

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
        printf("    %s: %d (%d seats)\n", play["name"].asString().c_str(), thisAmount, perf["audience"].asInt());
        totalAmount += thisAmount;
    }
    printf("Amount owed is %d\n", totalAmount );
    printf("You earned %d credits\n", volumeCredits);
}