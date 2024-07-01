#include "blackjack.h"

// TO-DO: guarantee only one "winner" / remove losers

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
        if (value >= 21) { // currently checking if one lost
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
int checkWinner(vector<vector<pair<int, int>>>& hands) {
    // winner id, hand value
    pair<int, int> winner(make_pair(-1, -1));

    // iterating over all hands
    for (size_t i = 0; i < hands.size(); ++i) {
        const auto& hand = hands[i];
        int hand_value = calculateHandValue(hand);

        if (hand_value > winner.second) {
            winner.first = i;
            winner.second = hand_value;
        }
    }

    return winner.first;
}

/**
 * @brief Prints a card into the terminal.
 * 
 * @param card The card to be printed.
 */
void printCard(const pair<int, int> card) {
    string rank = "";
    string suit = "";

    switch (card.first) {
        case 1:
            rank = "A";
            break;
        case 11:
            rank = "J";
            break;
        case 12:
            rank = "Q";
            break;
        case 13:
            rank = "K";
            break;
        default:
            rank = to_string(card.first);
    }

    switch (card.second) {
        case 1:
            suit = "♠";
            break;
        case 2:
            suit = "♥";
            break;
        case 3:
            suit = "♦";
            break;
        case 4:
            suit = "♣";
            break;
        default:
            cout << "Error getting card suit!\n";
    }

    cout << "(" << rank << ", " << suit << ")";
}

void printPlayerHand(const vector<pair<int, int>>& hand) {
    // Printing each card
    for (const auto& card : hand) {
        printCard(card);
        cout << ' ';
    }
}

/**
 * @brief Prints the blackjack table into the terminal.
 */
void printTable(const vector<vector<pair<int, int>>>& hands, const int turn) {
    cout << "======== BLACKJACK GAME TURN " << turn << "! ========\n";

    int player = 1;
    for (const auto& hand : hands) {
        cout << "Player " << player << " hand:\n";

        // Printing each card
        for (const auto& card : hand) {
            printCard(card);
            cout << ' ';
        }

        cout << "\n";
        player++;
    }

    cout << "=========================================\n";
}


