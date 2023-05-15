//---------------------------------------------------------------------
// Arquivo	: server.cpp
// Conteudo	: programa de um servidor para comunicação socket
// Autor	: Erick Sunclair (ericksunclair@ufmg.br)
// Data     : 14/05/2023
//---------------------------------------------------------------------

// bibliotecas padrao
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <filesystem>
// bibliotecas POSIX
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// tamanho do buffer padrão
#define BUFSZ 1024


int main(int argc, char *argv[]) {
    // erro de argumento(s) faltante(s)
    if (argc < 3) {
        std::cerr << "missing arguments, correct use: " << argv[0] << " [address_type] [port]" << std::endl;
        return 1;
    }

    // salva o tipo de endereco e a porta recebidos
    std::string address_type = argv[1];
    std::string port_str = argv[2];
    int port_int = std::stoi(port_str);

    // se o tipo desejado e o ipv6
    if(address_type == "v6"){
        // cria o SOCKET do servidor
        // AF_INET6 - familia de protocolos; SOCK_STREAM - tipo do socket - TCP
        int server_socket = socket(AF_INET6, SOCK_STREAM, 0);
        if (server_socket == -1) {
            std::cerr << "error while creating server socket" << std::endl;
            return 1;
        }

        // configurar o endereco do servidor                                // to fazneod tudo em ipv6, tem porlbema? nem to usanod o argv[1]
        struct sockaddr_in6 server_address{};
        server_address.sin6_family = AF_INET6;
        server_address.sin6_port = htons(port_int);
        server_address.sin6_addr = in6addr_any;

        // VINCULA o socket ao endereco do servidor
        if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
            std::cerr << "error while binding socket" << std::endl;
            return 1;
        }

        // ESCUTA por conexões de clientes
        if (listen(server_socket, 1) == -1) {
            std::cerr << "error while listening for connections" << std::endl;
            return 1;
        }

        std::cout << "server listening on port " << port_int << std::endl;

        while (1) {
            // ACEITA a conexão do cliente
            struct sockaddr_in6 client_address{};
            socklen_t client_address_size = sizeof(client_address);
            int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_size);
            if (client_socket == -1) {
                std::cerr << "error while accepting client connection" << std::endl;
                continue;
            }

            // converte o endereco IP do cliente, da familia AF_INET6, para string e 
            // salva no client_address_str para avisar que esse endereco esta conectado
            char client_address_str[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, &(client_address.sin6_addr), client_address_str, INET6_ADDRSTRLEN);
            std::cout << "client connected: " << client_address_str << std::endl;

            // RECEBE a mensagem do cliente
            char message_buffer[BUFSZ];
            memset(message_buffer, 0, BUFSZ);
            ssize_t bytes_read = recv(client_socket, message_buffer, BUFSZ, 0);

            // se nada foi recebido, retorna um erro
            if (bytes_read <= 0) {
                std::cerr << "error while receiving the message" << std::endl;
                // fecha a conexão com o cliente
                close(client_socket);
                continue;
            }

            // se a mensagem e exit, fecha a conexao
            if (std::string(message_buffer) == "exit") {
                std::string close_message = "connection closed";
                std::cout << close_message << std::endl;
                send(client_socket, close_message.c_str(), close_message.size(), 0);
                // fecha a conexão com o cliente
                close(client_socket);
                break;
            }
            // caso contrario, le a mensagem e cria o arquivo com o conteudo dela
            else {
                // pega o nome do arquivo no cabeçalho da mensagem
                std::string filename = std::string(message_buffer).substr(0, std::string(message_buffer).find_first_of("\n"));
                std::cout << "receiving file: " << filename << std::endl;

                // checa se o arquivo já existe
                bool file_existed;
                if (std::filesystem::exists(filename)) {
                    file_existed = true;
                } else {
                    file_existed = false;
                }

                // abre o arquivo para escrita
                std::ofstream file(filename, std::ios::out | std::ios::binary);
                
                // se nao consegue abrir o arquivo, envia aviso de erro
                if (!file) {
                    std::string error_message = "error receiving file " + filename;
                    send(client_socket, error_message.c_str(), error_message.size(), 0);

                    std::cerr << "error while opening file" << std::endl;
                    // fecha a conexão com o cliente
                    close(client_socket);
                    continue;
                }
                // se o arquivo foi aberto
                else {
                    // escreve no arquivo o conteudo da mensagem
                    std::string content = std::string(message_buffer).substr(std::string(message_buffer).find_first_of("\n") + 1);
                    file.write(content.c_str(), content.size());

                    // fecha o arquivo e avisa que ele foi recebido ou sobrescrito
                    file.close();
                    std::string success_message;
                    if (file_existed) {
                        success_message = "file " + filename + " overwritten";
                        std::cout << success_message << std::endl;
                    }
                    else {
                        success_message = "file " + filename + " received";
                        std::cout << success_message << std::endl;
                    }

                    // ENVIA ao cliente a confirmação de recebimento
                    send(client_socket, success_message.c_str(), success_message.size(), 0);
                }
                
            }
        }

        // FECHA o socket do servidor
        close(server_socket);
    }


    // se o tipo desejado e o ipv4
    else if(address_type == "v4"){
        // cria o SOCKET do servidor
        // AF_INET - familia de protocolos; SOCK_STREAM - tipo do socket - TCP
        int server_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (server_socket == -1) {
            std::cerr << "error while creating server socket" << std::endl;
            return 1;
        }

        // configurar o endereco do servidor
        struct sockaddr_in server_address{};
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(port_int);
        server_address.sin_addr.s_addr = INADDR_ANY;

        // VINCULA o socket ao endereco do servidor
        if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
            std::cerr << "error while binding socket" << std::endl;
            return 1;
        }

        // ESCUTA por conexões de clientes
        if (listen(server_socket, 1) == -1) {
            std::cerr << "error while listening for connections" << std::endl;
            return 1;
        }

        std::cout << "server listening on port " << port_int << std::endl;

        while (1) {
            // ACEITA a conexão do cliente
            struct sockaddr_in client_address{};
            socklen_t client_address_size = sizeof(client_address);
            int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_size);
            if (client_socket == -1) {
                std::cerr << "error while accepting client connection" << std::endl;
                continue;
            }

            // converte o endereco IP do cliente para string e salva no client_address_str
            char client_address_str[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(client_address.sin_addr), client_address_str, INET_ADDRSTRLEN);
            std::cout << "client connected: " << client_address_str << std::endl;

            // RECEBE a mensagem do cliente
            char message_buffer[BUFSZ];
            memset(message_buffer, 0, BUFSZ);
            ssize_t bytes_read = recv(client_socket, message_buffer, BUFSZ, 0);

            // se nada foi recebido, retorna um erro
            if (bytes_read <= 0) {
                std::cerr << "error while receiving the message" << std::endl;
                // fecha a conexão com o cliente
                close(client_socket);
                continue;
            }

            // se a mensagem é "exit", fecha a conexão
            if (std::string(message_buffer) == "exit") {
                std::string close_message = "connection closed";
                std::cout << close_message << std::endl;
                send(client_socket, close_message.c_str(), close_message.size(), 0);
                // fecha a conexão com o cliente
                close(client_socket);
                break;
            }
            // caso contrário, lê a mensagem e cria o arquivo com o conteúdo dela
            else {
                // obtém o nome do arquivo no cabeçalho da mensagem
                std::string filename = std::string(message_buffer).substr(0, std::string(message_buffer).find_first_of("\n"));
                std::cout << "receiving file: " << filename << std::endl;

                // verifica se o arquivo já existe
                bool file_existed = std::filesystem::exists(filename);

                // abre o arquivo para escrita
                std::ofstream file(filename, std::ios::out | std::ios::binary);

                // se não consegue abrir o arquivo, envia aviso de erro
                if (!file) {
                    std::string error_message = "error receiving file " + filename;
                    send(client_socket, error_message.c_str(), error_message.size(), 0);

                    std::cerr << "error while opening file" << std::endl;
                    // fecha a conexão com o cliente
                    close(client_socket);
                    continue;
                }
                // se o arquivo foi aberto
                else {
                    // escreve no arquivo o conteúdo da mensagem
                    std::string content = std::string(message_buffer).substr(std::string(message_buffer).find_first_of("\n") + 1);
                    file.write(content.c_str(), content.size());

                    // fecha o arquivo e avisa que ele foi recebido ou sobrescrito
                    file.close();
                    std::string success_message;
                    if (file_existed) {
                        success_message = "file " + filename + " overwritten";
                        std::cout << success_message << std::endl;
                    }
                    else {
                        success_message = "file " + filename + " received";
                        std::cout << success_message << std::endl;
                    }

                    // ENVIA ao cliente a confirmação de recebimento
                    send(client_socket, success_message.c_str(), success_message.size(), 0);
                }
            }
        }

        // FECHA o socket do servidor
        close(server_socket);
    }


    return 0;
}