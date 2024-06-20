#include "config.h"
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

vector<pair<int, int>> generateDeck() {
    vector<pair<int, int>> deck;
    for (int suit = 1; suit <= 4; ++suit) {
        for (int rank = 1; rank <= 13; ++rank) {
            deck.push_back(make_pair(rank, suit));
        }
    }

    // random seed
    random_device rd;

    // gerando numeros aleatorios bons
    mt19937 g(rd());

    // Shuffle the deck
    shuffle(deck.begin(), deck.end(), g);
    
    return deck;
}