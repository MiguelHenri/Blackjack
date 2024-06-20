#include <iostream>

class Player {
    vector<pair<int, int>> hand;

    public:
        void playTurn(Dealer& dealer) {
            // Get initial two cards
            hand.push_back(dealer.dealCard());
            hand.push_back(dealer.dealCard());

            // Continue to draw cards while hand value is less than 17
            while (dealer.calculateHandValue(hand) < 17) {
                hand.push_back(dealer.dealCard());
            }
        }
};