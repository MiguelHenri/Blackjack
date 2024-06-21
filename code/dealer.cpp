#include "dealer.h"

/**
 * @brief Dealer constructor.
 * 
 * @return Dealer object.
 */
Dealer::Dealer() {
    // Initialize the deck with all cards
    for (int suit = 1; suit <= 4; ++suit) {
        for (int rank = 1; rank <= 13; ++rank) {
            deck.push_back(make_pair(rank, suit));
        }
    }

    // Getting random seed
    random_device rd;
    mt19937 g(rd());

    // Shuffle the deck
    shuffle(deck.begin(), deck.end(), g);
}

/**
 * @brief Getting a card from the deck and removing it.
 * 
 * @return The card to be dealt from the deck.
 */
pair<int, int> Dealer::dealCard() {
    pair<int, int> card = deck.back(); 
    deck.pop_back();
    return card; 
}

void Dealer::printDeck() {
    for (const auto& card : deck) {
        cout << card.first << ' ' << card.second << '\n';
    }
}