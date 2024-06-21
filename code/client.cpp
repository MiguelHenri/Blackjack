#include "config.h"

int main() {
    // Initializing variables
    int server_socket = -1;
    struct sockaddr_in server_addr;

    // Building socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        cerr << "Erro ao criar o socket\n";
        return 1;
    }

    // Configuring server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    // Connecting to server
    if (connect(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0) {
        cerr << "Erro ao conectar ao servidor\n";
        close(server_socket);
        return 1;
    }

    // Continuously receiving messages
    char msg;
    while (true) {
        if (recv(server_socket, &msg, sizeof(msg), 0) == -1) {
            cerr << "Erro ao receber a mensagem\n";
            break;
        }
        // else{
        //     cout << "recebi" << endl;
        // }

        cout << "Mensagem recebida do servidor: " << msg << endl;
    }

    // Closing socket
    close(server_socket);

    return 0;
}