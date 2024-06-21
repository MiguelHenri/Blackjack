#include "dealer.h"
#include "config.h"

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

/**
 * @brief Calculates some player's hand value.
 * 
 * @param hand The player's hand.
 * @return The hand value.
 */
int Dealer::calculateHandValue(const vector<pair<int, int>>& hand) {
    int value = 0;

    // Iterate through each card in the hand
    for (const auto& card : hand) {
        int rank = card.first; 
        if (rank > 10) {
            value += 10;  // Face cards are worth 10
        } else if (rank == 1) {
            value += ACE_VALUE;  // Getting ace value from config
        } else {
            value += rank;
        }
    }

    return value;
}