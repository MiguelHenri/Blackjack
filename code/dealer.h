#ifndef DEALER_H
#define DEALER_H

#include "config.h"
#include <algorithm>
#include <random>

using namespace std;

class Dealer {
private:
    vector<pair<int, int>> deck;

public:
    Dealer();
    pair<int, int> dealCard();
    int calculateHandValue(const vector<pair<int, int>>& hand);
};

#endif