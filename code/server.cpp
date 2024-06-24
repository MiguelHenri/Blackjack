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

    // Initializing players hands with one cards
    for (auto& hand : hands) {
        hand.push_back(dealer.dealCard());
    }
    printTable(hands);

    // Running game
    do {
        // TO-DO: players should tell if they want to retrieve a card.
        // Retrieving new cards for each player
        for (auto& hand : hands) {
            hand.push_back(dealer.dealCard());
        }

        // Serializing players hands data
        string data = serialize(hands);

        // Sending players hands to the players themselves
        for (int i=0; i<NUM_PLAYERS; i++) {
            if (send(connect_socket[i], data.c_str(), data.size(), 0) < 0) {
                cerr << "Error sending message to player " << i << ".\n";
                for (int sock : connect_socket) {
                    close(sock);
                }
                close(server_socket);
                return 1;
            } else {
                cout << "Message sent to player " << i << ".\n";
            }
        }
    } while (inGame(hands)); // Always checking if game ended

    // TODO: check winner

    for (int sock : connect_socket) {
        close(sock);
    }

    cout << "Reached the end of the program." << endl;
    close(server_socket);

    return 0;
}