//---------------------------------------------------------------------
// Arquivo	: user.cpp
// Conteudo	: programa de um cliente (usuário) para comunicação socket
// Autor	: Erick Sunclair (ericksunclair@ufmg.br)
// Data     : 05/06/2023
//---------------------------------------------------------------------

// bibliotecas padrao
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
// bibliotecas POSIX
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

// tamanho do buffer padrão
#define BUFSZ 1024
// variavel para sinalizar quando o cliente deve ser fechado
bool close_client = 0;

// funcao para receber mensagem do servidor a qualquer momento
void* wait_recv (void* socket)
{
    int client_socket = *(int*) socket;
    while(1)
    {
        // RECEBE uma resposta do servidor
        char response[BUFSZ];
        std::memset(response, 0, sizeof(response));         // limpa espaço da memoria (buffer)
        int bytes_read = recv(client_socket, response, sizeof(response), 0);
        if (bytes_read == -1) {
            std::cerr << "Error while receiving message from the server" << std::endl;
            continue;
        }
        else if (bytes_read == 0) {
            std::cerr << "Cannot receive messages from the server. Press Enter to exit" << std::endl;
            close_client = 1;
            break;
        }
        std::string str_response(response);
        // se recebe mensagem de conexao fechada ou sala cheia, fecha o cliente
        if ((str_response == "Removed Successfully") || (str_response == "User limit exceeded")) {
            // imprime a resposta no terminal
            std::cout << response << std::endl;
            close_client = 1;
            break;
        }

        // imprime a resposta no terminal
        std::cout << response << std::endl;
    }
    // fecha a thread aberta
    pthread_exit(NULL);
}


int main (int argc, char *argv[]) {
    // erro de argumento(s) faltante(s)
    if (argc < 3) {
        std::cerr << "Missing arguments, correct use: " << argv[0] << " [IPaddress] [port]" << std::endl;
        return 1;
    }

    // salva o endereço IP e a porta recebidos
    std::string ip_address = argv[1];
    std::string port_str = argv[2];
    int port_int = std::stoi(port_str);

    // cria o SOCKET do cliente
    // AF_INET - familia de protocolos; SOCK_STREAM - tipo do socket - TCP
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        std::cerr << "Error while creating client socket" << std::endl;
        return 1;
    }

    // cria estrutura de enderecamento de rede para o servidor
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;            // familia do endereco
    server_address.sin_port = htons(port_int);          // porta do endereco no formato "network short"
    // converte o endereco IP (string) para uma estrutura de endereco de rede da familia AF_INET
    // e salva no server_address.sin_addr, ja tratando possivel erro de endereço IP invalido
    if (inet_pton(AF_INET, ip_address.c_str(), &(server_address.sin_addr)) <= 0) {          // endereco
        std::cerr << "Invalid IP address" << std::endl;
        return 1;
    }
    // obs: usei AF_INET (IPv4) porque assim o cliente é capaz de se conectar a servidores IPv4 e IPv6

    // CONECTA o socket do cliente ao endereco do servidor
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        std::cerr << "Error while connecting to server" << std::endl;
        return 1;
    }

    // cria thread para receber mensagem do servidor a qualquer momento
    pthread_t thread_recv;
    pthread_create(&thread_recv, NULL, &wait_recv, (void*) &client_socket);

    // loop principal do cliente
    while (1) {
        // espera um tempo por uma possivel modificaçao na variavel close_client
        usleep(0.5 * 1000000);  // 0.5 segundos
        // fecha o cliente caso seja sinalizado
        if (close_client == 1)  break;

        // espera pelo comando do usuario
        std::string command;
        // std::cout << "Type a command: ";
        std::getline(std::cin, command);

        // Envia a mensagem para o servidor
        if (send(client_socket, command.c_str(), command.size(), 0) == -1) {
            std::cerr << "Error while sending message to server" << std::endl;
            close(client_socket);
            return 1;
        }
    }

    // FECHA a conexão com o servidor
    close(client_socket);
    // fecha possiveis threads abertas
    pthread_exit(NULL);

    return 0;
}
