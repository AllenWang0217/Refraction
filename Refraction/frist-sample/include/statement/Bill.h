#pragma once
#include <string>
#include <vector>
#include <iostream>
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
