#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "config.h"

bool inGame(const vector<vector<pair<int, int>>>& hands);
int calculateHandValue(const vector<pair<int, int>>& hand);
void printTable(const vector<vector<pair<int, int>>>& hands, const int turn);

#endif