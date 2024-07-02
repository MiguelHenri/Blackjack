#include "config.h"
#include "dealer.h"
#include "blackjack.h"

int main() {
    // Initializing variables
    vector<int> connect_socket;
    int server_socket = -1;
    struct sockaddr_in server_addr, client_addr;
    socklen_t len;

    // Building socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    // AF_INET: defines IPV4 protocol.
    // SOCK_STREAM: defines TCP socket.
    if (server_socket == -1) {
        cerr << "Error creating socket.\n";
        return 1;
    }

    // Configuring server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    // Binding address to socket
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0) {
        cerr << "Error binding address to socket.\n";
        close(server_socket);
        return 1;
    }

    // Put socket to listen
    if (listen(server_socket, 2) != 0) { // We expect at most 2 clients
        cerr << "Error putting socket in listening mode.\n";
        close(server_socket);
        return 1;
    }
    cout << "Server is running in port: " << PORT << "\n";

    // Trying to connect with players (clients)
    int player_count = 0;
    while (player_count < NUM_PLAYERS) {
        cout << "Waiting for " << 2 - player_count << " players to connect...\n";
        len = sizeof(client_addr);
        int tmp = accept(server_socket, (struct sockaddr*)&client_addr, &len);
        if (tmp < 0) {
            cerr << "Error accepting connection.\n";
            close(server_socket);
            return 1;
        } else {
            connect_socket.push_back(tmp);
            player_count++;
        }
    }

    // Starting game
    cout << "Players connected! Starting...\n";
    Dealer dealer; // Dealer object
    vector<vector<pair<int, int>>> hands(NUM_PLAYERS); // Players hands
    vector<bool> still_playing(NUM_PLAYERS, true);
    bool its_over = false;

    // Initializing players hands with two cards
    for (auto& hand : hands) {
        hand.push_back(dealer.dealCard());
        hand.push_back(dealer.dealCard());
    }

    // Running game
    do {
        string data;
        // Checking if the Game ended!
        if (its_over || allLost(hands)) {
            // We still need to inform the players
            its_over = true;
            data = "GAME OVER";
        }
        else { // Serializing players hands data
            data = serialize(hands);
        }

        // Sending players hands to the players themselves
        // or informing the game ended
        for (int i=0; i<NUM_PLAYERS; i++) {

            if (send(connect_socket[i], data.c_str(), data.size(), 0) < 0) {
                cerr << "Error sending table to player " << i + 1 << ".\n";
                for (int sock : connect_socket) {
                    close(sock);
                }
                close(server_socket);
                return 1;
            } else {
                cout << "Table sent to player " << i + 1<< ".\n";
            }
        }

        // Breaking loop if game ended
        if (its_over) break;

        // Asking players if thy want to retrieve a new card.
        for (int i=0; i<NUM_PLAYERS; i++) {

            // msg tells the players who they are
            char msg = '0' + i;
            char response;

            // Sending message indicating server is ready to receive message
            if (send(connect_socket[i], &msg, sizeof(msg), 0) == -1) {
                cerr << "Error asking player " << i + 1 << ".\n";
                for (int sock : connect_socket) {
                    close(sock);
                }
                return 1;
            }
            // Receiving player message
            if (recv(connect_socket[i], &response, sizeof(response), 0) == -1) {
                cerr << "Error receiving player " << i + 1 << " response.\n";
                for (int sock : connect_socket) {
                    close(sock);
                }
                return 1;
            }
            cout << "Message sent to player: " << i + 1 << ".\n";
            // Checking player answer
            if (response == 'y' || response == 'Y') {
                // Retrieving new card to player hand
                hands[i].push_back(dealer.dealCard());
                still_playing[i] = true;
            }
            else if (response == 'n' || response == 'N'){
                still_playing[i] = false;
            }
            else {
                cerr << "Bad player " << i + 1 << " response.\n";
                for (int sock : connect_socket) {
                    close(sock);
                }
                return 1;
            }
        }

        // If all players said they dont want to retrieve a new card
        if (all_of(still_playing.begin(), still_playing.end(), [](bool v) { 
            return v == false; })) {
            its_over = true; // end game
        }

    } while (true);

    // Message to inform the winner
    int winner = checkWinner(hands);

    // Informing players who won!
    for (int i=0; i<NUM_PLAYERS; i++) {
        if (send(connect_socket[i], &winner, sizeof(winner), 0) == -1) {
            cerr << "Error senting winner to player " << i + 1 << ".\n";
            for (int sock : connect_socket) {
                close(sock);
            }
            return 1;
        } else {
            cout << "Winner sent to player " << i + 1 << ".\n";
        }
    }

    for (int sock : connect_socket) {
        close(sock);
    }

    cout << "Reached the end of the game." << endl;
    close(server_socket);

    return 0;
}