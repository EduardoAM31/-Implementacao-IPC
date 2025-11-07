#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024
#define SHIFT 3 // chave da cifra de César

void encrypt(char *mensagem) {
    for (int i = 0; mensagem[i] != '\0'; i++) {
        mensagem[i] = mensagem[i] + SHIFT;
    }
}

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    char mensagem[BUFFER_SIZE];

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
    fgets(mensagem, BUFFER_SIZE, stdin);
    mensagem[strcspn(mensagem, "\n")] = '\0';

    encrypt(mensagem);
    send(sock, mensagem, strlen(mensagem), 0);
    printf("Mensagem criptografada enviada: %s\n", mensagem);

    closesocket(sock);
    WSACleanup();

    return 0;
}
