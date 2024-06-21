#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "config.h"

int calculateHandValue(const vector<pair<int, int>>& hand);
void printTable(const vector<pair<int, int>>& hand);

#endif