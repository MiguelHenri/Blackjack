#include "config.h"
#include "blackjack.h"

int main() {
    // Initializing variables
    int server_socket = -1;
    struct sockaddr_in server_addr;

    // Building socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        cerr << "Error creating socket.\n";
        return 1;
    }

    // Configuring server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    // Connecting to server
    if (connect(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0) {
        cerr << "Error connecting to server.\n";
        close(server_socket);
        return 1;
    }

    // Running game
    // Initializing players hands
    vector<vector<pair<int, int>>> hands(NUM_PLAYERS);
    do {
        char buffer[1024];
        // TO-DO: players should be able to send a message telling 
        // if they want to retrieve a card or not.
        ssize_t bytesRead = recv(server_socket, buffer, sizeof(buffer), 0);
        if (bytesRead < 0) {
            cerr << "Error receiving message.\n";
            return 1;
        } else {
            cout << "Message received.\n";

            buffer[bytesRead] = '\0';
            string data(buffer, bytesRead);

            hands = deserialize(data);

            printTable(hands);
        }
    } while (inGame(hands));

    // Closing socket
    close(server_socket);

    return 0;
}