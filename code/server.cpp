#include "config.h"

int main() {
    // Initializing variables
    vector<int> connect_socket;
    int server_socket = -1;
    struct sockaddr_in server_addr, client_addr;
    socklen_t len;

    // Building socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        cerr << "Error creating socket\n";
        return 1;
    }

    // Configuring server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    // Binding address to socket
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0) {
        cerr << "Error binding address to socket\n";
        close(server_socket);
        return 1;
    }

    // Put socket to listen
    if (listen(server_socket, 2) != 0) { // We expect at most 2 clients
        cerr << "Error putting socket in listening mode\n";
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
            cerr << "Error accepting connection\n";
            close(server_socket);
            return 1;
        } else {
            connect_socket.push_back(tmp);
            player_count++;
        }
    }

    char msg = 'A';
    
    if (send(connect_socket[0], &msg, sizeof(msg), 0) == -1) {
        cerr << "Error sending message\n";
        for (int sock : connect_socket) {
            close(sock);
        }
        close(server_socket);
        return 1;
    }
    if (send(connect_socket[1], &msg, sizeof(msg), 0) == -1) {
        cerr << "Error sending message\n";
        for (int sock : connect_socket) {
            close(sock);
        }
        close(server_socket);
        return 1;
    }
    

    for (int sock : connect_socket) {
        close(sock);
    }

    cout << "Reached the end of the program" << endl;
    close(server_socket);

    return 0;
}