#include "config.h"

int main() {
    // Initializing variables
    int server_socket = -1;
    int connect_socket = -1;
    struct sockaddr_in server_addr, client_addr;
    socklen_t len;

    // Building socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        cerr << "Erro ao criar o socket\n";
        return 1;
    }

    // Configuring server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    // Binding address to socket
    if ((bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr))) != 0) {
        cerr << "Erro ao associar o endereço ao socket\n";
        close(server_socket);
        return 1;
    }

    // Put socket to listen
    if ((listen(server_socket, 5)) != 0) {
        cerr << "Erro ao colocar o socket em modo de escuta\n";
        close(server_socket);
        return 1;
    }

    int player_count = 0;
    while (true && player_count <= 2) {
        // Connecting 
        len = sizeof(client_addr);
        connect_socket = accept(server_socket, (struct sockaddr*)&client_addr, &len);
        if (connect_socket < 0) {
            cerr << "Erro ao aceitar a conexão\n";
            close(server_socket);
            return 1;
        } else {
            player_count++;
        }

        // Sending char
        char msg = 'A';
        if (send(connect_socket, &msg, sizeof(msg), 0) == -1) {
            cerr << "Erro ao enviar a mensagem\n";
            close(connect_socket);
            close(server_socket);
            return 1;
        }

        // Closing connection socket
        close(connect_socket);
    }
    close(server_socket);

    return 0;
}