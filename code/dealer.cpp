#include "config.h"
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

class Dealer {
    vector<pair<int, int>> deck;

    public:
        Dealer() {
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
        }

        pair<int, int> dealCard() {
            pair<int, int> card = deck.back();
            deck.pop_back();
            return card;
        }

        int calculateHandValue(const vector<pair<int, int>>& hand) {
            int value = 0;
            int aceCount = 0;

            for (const auto& card : hand) {
                int rank = card.first;
                if (rank > 10) {
                    value += 10;  // Face cards are worth 10
                } else if (rank == 1) {
                    value += 11;  // Aces are initially worth 11
                    aceCount++;
                } else {
                    value += rank;
                }
            }

            // If we have aces and our value is over 21, reduce the value by 10 for each ace
            while (value > 21 && aceCount > 0) {
                value -= 10;
                aceCount--;
            }

            return value;
        }

        void game() {
            String ready1, ready2;
            while ()
        }
}
