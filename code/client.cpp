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
    bool continue_playing = true;
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

            // Checking if game is over
            if (strncmp(data.c_str(), "GAME OVER", 9) == 0) {
                // reached the end of the game
                break;
            }
            else {
                hands = deserialize(data);

                printTable(hands, turn);
                turn++;
            }
        }

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
        if (status < '0' || status > '9') { // Oops... Something wrong.
            cerr << "Unhandled error receiving server status.\n";
            close(server_socket);
            return 1;
        } else { // Ok! Let's play!
            cout << "Hi Player " << status - '0' + 1 << "!\n";
            cout << "Do you want to retrieve a new card? [y/n]\n";
            cin >> msg;
            if (msg == 'n' || msg == 'N') continue_playing = false;

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

    // We reached the end of the game!
    // Getting winner from server
    int winner;
    if (recv(server_socket, &winner, sizeof(winner), 0) == -1) {
        cerr << "Error receiving winner from server.\n";
        close(server_socket);
        return 1;
    }

    if (winner != -1) {
        cout << "Player " << to_string(winner) << " has won the game!\n";
    } else {
        cout << "No one has won the game :(\n";
    }

    cout << "GAME OVER!\n";
    // Closing socket
    close(server_socket);

    return 0;
}