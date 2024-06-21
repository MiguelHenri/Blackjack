#include "blackjack.h"

/**
 * @brief Calculates some player's hand value.
 * 
 * @param hand The player's hand.
 * @return The hand value.
 */
int calculateHandValue(const vector<pair<int, int>>& hand) {
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

/**
 * @brief Checks if the game is ongoing.
 * 
 * @param hands The players' hands.
 * @return True if game is ongoing, false if not.
 */
bool inGame(const vector<vector<pair<int, int>>>& hands) {
    bool check = true;

    // Iterates through all players hands
    for (const auto& hand : hands) {
        int value = calculateHandValue(hand);
        if (value >= 21) {
            check = false;
        }
    }

    return check;
}

/**
 * @brief Checks who is the winner.
 * 
 * @param hands The players' hands.
 * @return The winner hand position.
 */
int checkWinner() {
    
}

/**
 * @brief Prints the blackjack table.
 */
void printTable(const vector<vector<pair<int, int>>>& hands) {
    
}


