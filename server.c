#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024
#define SHIFT 3 // chave da cifra de César

void decrypt(char *message) {
    for (int i = 0; message[i] != '\0'; i++) {
        message[i] = message[i] - SHIFT;
    }
}

int main() {
    WSADATA wsa;
    SOCKET server_fd, client_socket;
    struct sockaddr_in server, client;
    int c;
    char buffer[BUFFER_SIZE] = {0};

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Falha ao inicializar. Codigo de erro: %d\n", WSAGetLastError());
        return 1;
    }

    // Criar socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Nao foi possivel criar o socket. Erro: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Bind
    if (bind(server_fd, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Erro no bind. Codigo: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // Listen
    listen(server_fd, 3);

    c = sizeof(struct sockaddr_in);
    client_socket = accept(server_fd, (struct sockaddr *)&client, &c);
    if (client_socket == INVALID_SOCKET) {
        printf("Falha ao aceitar conexao. Erro: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // Recebe mensagem
    int recv_size = recv(client_socket, buffer, BUFFER_SIZE, 0);
    if (recv_size == SOCKET_ERROR) {
        printf("Erro ao receber mensagem.\n");
    } else {
        buffer[recv_size] = '\0';
        printf("Mensagem criptografada recebida: %s\n", buffer);
        decrypt(buffer);
        printf("Mensagem decifrada: %s\n", buffer);
    }

    closesocket(client_socket);
    closesocket(server_fd);
    WSACleanup();

    return 0;
}
