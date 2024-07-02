#ifndef DEALER_H
#define DEALER_H

#include "config.h"
#include <algorithm>
#include <random>

class Dealer {
private:
    vector<pair<int, int>> deck;

public:
    Dealer();
    pair<int, int> dealCard();
};

#endif