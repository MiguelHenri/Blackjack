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

    // Starting game
    cout << "Waiting for other players...\n";
    // Initializing players hands
    vector<vector<pair<int, int>>> hands(NUM_PLAYERS);
    int turn = 1;
    do {
        // Getting the game current status from server and priting table
        char buffer[1024];
        ssize_t bytesRead = recv(server_socket, buffer, sizeof(buffer), 0);
        if (bytesRead < 0) {
            cerr << "Error receiving message.\n";
            close(server_socket);
            return 1;
        } else {
            buffer[bytesRead] = '\0';
            string data(buffer, bytesRead);

            hands = deserialize(data);

            printTable(hands, turn);
            turn++;
        }

        // TODO: maybe we can clear the terminal?

        // Always checking if game ended
        if (!inGame(hands)) break;

        cout << "Keep waiting for your turn...\n";
        // Checking if it's our turn
        char status;
        char msg;
        if (recv(server_socket, &status, sizeof(status), 0) == -1) {
            cerr << "Error receiving server status.\n";
            close(server_socket);
            return 1;
        }
        // Ok! It's our turn
        if (status != 's') { // Oops... Something wrong.
            cerr << "Unhandled error receiving server status.\n";
            close(server_socket);
            return 1;
        } else { // Ok! Let's play!
            cout << "Do you want to retrieve a new card? [y/n]\n";
            cin >> msg;
            // Sending our answer to server
            if (send(server_socket, &msg, sizeof(msg), 0) == -1) {
                cerr << "Error sending answer to server.\n";
                close(server_socket);
                return 1;
            }
        }

        // Now, we're waiting other players turn
        cout << "Waiting for other players turn...\n";
    } while (true);

    // Closing socket
    close(server_socket);

    return 0;
}