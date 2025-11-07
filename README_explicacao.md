# Explicação do Código Cliente-Servidor com Sockets (Windows)

Este projeto implementa uma comunicação **cliente-servidor** simples em linguagem C utilizando **Winsock2**, a biblioteca de sockets do Windows. 
O objetivo é demonstrar como duas aplicações podem se comunicar por meio de uma conexão TCP/IP, trocando mensagens.

---

## 🖥️ Estrutura do Projeto

O projeto possui dois arquivos principais:

- `server.c` → Representa o **servidor**, responsável por aguardar e responder conexões.
- `cliente.c` → Representa o **cliente**, responsável por enviar mensagens ao servidor.

---

## ⚙️ Funcionamento Geral

1. O servidor é iniciado e fica aguardando uma conexão em uma porta específica (porta 8080 neste caso).
2. O cliente é executado, cria uma conexão com o servidor e envia uma mensagem.
3. O servidor recebe essa mensagem, exibe no terminal e envia uma resposta.
4. O cliente recebe a resposta do servidor e exibe na tela.
5. Ambos encerram a comunicação.

---

## 🧩 Explicação do Código do Servidor (`server.c`)

1. **Inicialização da biblioteca Winsock**
   ```c
   WSAStartup(MAKEWORD(2,2), &wsa);
   ```
   Antes de usar qualquer função de rede no Windows, é necessário inicializar a biblioteca **Winsock**. 
   Essa função carrega as dependências de rede e prepara o ambiente para o uso de sockets.

2. **Criação do socket**
   ```c
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   ```
   Aqui é criado um socket do tipo **TCP** (`SOCK_STREAM`) e **IPv4** (`AF_INET`). Esse socket será usado para escutar conexões.

3. **Configuração do endereço**
   ```c
   addr.sin_family = AF_INET;
   addr.sin_port = htons(8080);
   addr.sin_addr.s_addr = INADDR_ANY;
   ```
   Define que o servidor usará IPv4, escutará na porta 8080 e aceitará conexões de qualquer endereço IP.

4. **Associação do socket à porta (bind)**
   ```c
   bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
   ```
   Associa o socket criado ao endereço e porta definidos acima.

5. **Escuta por conexões (listen)**
   ```c
   listen(sockfd, 1);
   ```
   Coloca o socket em modo de escuta, permitindo receber conexões de clientes. 
   O parâmetro `1` indica o número máximo de conexões pendentes.

6. **Aceitar conexão**
   ```c
   clientfd = accept(sockfd, NULL, NULL);
   ```
   Aguarda até que um cliente se conecte. Quando isso acontece, retorna um novo socket específico para essa comunicação.

7. **Receber mensagem do cliente**
   ```c
   recv(clientfd, buffer, sizeof(buffer), 0);
   ```
   Recebe dados enviados pelo cliente e armazena no buffer.

8. **Enviar resposta ao cliente**
   ```c
   send(clientfd, resposta, strlen(resposta), 0);
   ```
   Envia uma mensagem de volta confirmando o recebimento.

9. **Fechamento dos sockets e limpeza**
   ```c
   closesocket(clientfd);
   closesocket(sockfd);
   WSACleanup();
   ```
   Fecha as conexões e libera os recursos utilizados pela biblioteca Winsock.

---

## 💻 Explicação do Código do Cliente (`cliente.c`)

1. **Inicialização da Winsock**
   ```c
   WSAStartup(MAKEWORD(2,2), &wsa);
   ```
   Assim como no servidor, o cliente também precisa inicializar a biblioteca antes de usar funções de rede.

2. **Criação do socket**
   ```c
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   ```
   Cria um socket TCP/IP para a conexão.

3. **Definição do endereço do servidor**
   ```c
   addr.sin_family = AF_INET;
   addr.sin_port = htons(8080);
   inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
   ```
   Configura a conexão para o IP `127.0.0.1` (localhost) e porta `8080`, o mesmo do servidor.

4. **Conexão com o servidor**
   ```c
   connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));
   ```
   Tenta estabelecer uma conexão com o servidor. Caso o servidor esteja em execução, a conexão será aceita.

5. **Envio de mensagem**
   ```c
   send(sockfd, mensagem, strlen(mensagem), 0);
   ```
   Envia uma mensagem ao servidor. No exemplo, a string `"Ola servidor!"` é enviada.

6. **Recebimento da resposta**
   ```c
   recv(sockfd, buffer, sizeof(buffer), 0);
   ```
   Recebe a resposta enviada pelo servidor e armazena no buffer.

7. **Encerramento da conexão**
   ```c
   closesocket(sockfd);
   WSACleanup();
   ```
   Fecha o socket e limpa os recursos de rede.

---

## 🧠 Resumo do Fluxo de Comunicação

```
Cliente --> (send) --> Servidor
Servidor --> (recv) --> Servidor exibe mensagem
Servidor --> (send) --> Cliente
Cliente --> (recv) --> Cliente exibe resposta
```

---

## 🧾 Observações

- Este exemplo usa **TCP** (orientado à conexão), garantindo entrega confiável dos dados.
- A comunicação ocorre localmente em `127.0.0.1` (localhost).
- Para conexões em rede real, basta substituir o IP pelo endereço da máquina do servidor.
- O código foi testado e compilado no Windows com o compilador **MinGW**.

---

## 🛠️ Comandos de Compilação

```bash
gcc server.c -o server -lws2_32
gcc cliente.c -o cliente -lws2_32
```

Depois, execute em dois terminais separados:

**Terminal 1 (Servidor):**
```bash
server.exe
```

**Terminal 2 (Cliente):**
```bash
cliente.exe
```

---

✅ **Em resumo:**  
O código demonstra a base da comunicação entre processos via rede, utilizando sockets TCP no Windows. 
Ele é ideal como exemplo introdutório para estudos de **Interprocess Communication (IPC)**, **redes** e **arquitetura cliente-servidor**.
