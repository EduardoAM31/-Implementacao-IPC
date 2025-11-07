#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024
#define SHIFT 3 // chave da cifra de César

void encrypt(char *message) {
    for (int i = 0; message[i] != '\0'; i++) {
        message[i] = message[i] + SHIFT;
    }
}

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    char message[BUFFER_SIZE];

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Falha ao inicializar. Codigo de erro: %d\n", WSAGetLastError());
        return 1;
    }

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Nao foi possivel criar o socket. Erro: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Erro ao conectar.\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    printf("Digite uma mensagem: ");
    fgets(message, BUFFER_SIZE, stdin);
    message[strcspn(message, "\n")] = '\0';

    encrypt(message);
    send(sock, message, strlen(message), 0);
    printf("Mensagem criptografada enviada: %s\n", message);

    closesocket(sock);
    WSACleanup();

    return 0;
}
