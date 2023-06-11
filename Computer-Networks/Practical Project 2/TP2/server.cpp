//---------------------------------------------------------------------
// Arquivo	: server.cpp
// Conteudo	: programa de um servidor para comunicação socket multi-thread
// Autor	: Erick Sunclair (ericksunclair@ufmg.br)
// Data     : 05/06/2023
//---------------------------------------------------------------------

// bibliotecas padrao
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <set>
#include <iomanip>
#include <ctime>
// bibliotecas POSIX
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <semaphore.h>

// tamanho do buffer padrão
#define BUFSZ 1024
// numero maximo de usuarios
#define MAX_USERS 15
// numero de usuarios conectados
int connected_users = 0;
// set de usuarios conectados
std::set<int> users_set;
// set de sockets dos clientes conectados
std::set<int> sockets_set;
// semaforo a ser usado para compartilhamento de recursos pelas threads
sem_t semaphore;


// funcao que transforma um set de usuarios em uma string
std::string set_to_str (std::set<int>* set) {
    std::string string;
    for (int num : *set) {
        if (num<10) string.append("0");
        string.append(std::to_string(num));
        string.append(" ");
    }
    return string;
}

// funcao que retorna um timestamp com o formato [HH:MM]
std::string current_time () {
    auto raw_time = std::time(nullptr);
    auto time = *std::localtime(&raw_time);
    std::ostringstream oss;
    oss << std::put_time(&time, "%H:%M");
    auto str = "[" + oss.str() + "]";
    return str;
}

// funcao para tratar um cliente individualmente
void* client_handler (void* socket) {
    int client_socket = *(int*)socket;
    int user_index = -1;
    std::string str_user_index = "";

    // escolhe o indice para o novo cliente
    for (int i=1; i<16; i++) {
        if (users_set.find(i) == users_set.end()) {
            user_index = i;
            
            // salva o index em formato para impressao
            if (user_index<10)
                str_user_index.append("0");
            str_user_index.append(std::to_string(user_index));

            break;
        }
    }
    if (user_index == -1) {
        std::cerr << "Error while assigning an index to new user" << std::endl;
        // finaliza a thread
        pthread_exit(NULL);
    }

    // incrementa o numero de usuarios conectados
    connected_users++;
    // adiciona o novo usuario no set de usuarios conectados
    users_set.insert(user_index);
    // adiciona o socket do novo cliente no set de sockets
    sockets_set.insert(client_socket);
    // avisa no terminal que foi adicionado um usuario
    std::cout << "User " << str_user_index << " added" << std::endl;

    // std::cout << "Connected users: " << set_to_str(&users_set) << "(" << connected_users << " users)" << std::endl;   // APENAS PARA TESTE
    // std::cout << "Connected sockets: " << set_to_str(&sockets_set) << std::endl;    // APENAS PARA TESTE

    // ENVIA ao cliente o aviso de que ele foi conectado
    std::string message = "User " + str_user_index + " joined the group!";
    // aguarda permissão para acessar o recurso compartilhado
    sem_wait(&semaphore);
    for (std::set<int>::iterator it = sockets_set.begin(); it != sockets_set.end(); ++it)
        send(*it, message.c_str(), message.size(), 0);
    // libera o recurso compartilhado
    sem_post(&semaphore);

    while(1) {
        // RECEBE a mensagem do cliente
        char message_buffer[BUFSZ];
        memset(message_buffer, 0, BUFSZ);
        ssize_t bytes_read = recv(client_socket, message_buffer, BUFSZ, 0);

        // se nada foi recebido, retorna um erro
        if (bytes_read == -1) {
            std::cerr << "Error while receiving the message" << std::endl;
            continue;
        }
        else if (bytes_read == 0) {
            std::cerr << "Cannot receive messages from User " << str_user_index << ". He will be disconnected" << std::endl;
            // avisa no terminal que a conexao foi fechada
            std::cout << "User " << str_user_index << " removed" << std::endl;
            break;
        }

        // se a mensagem for "close connection", fecha a conexão
        if (std::string(message_buffer) == "close connection") {
            // avisa no terminal que a conexao foi fechada
            std::cout << "User " << str_user_index << " removed" << std::endl;

            // ENVIA ao cliente a confirmação de recebimento
            std::string close_message = "Removed successfully";
            // aguarda permissão para acessar o recurso compartilhado
            sem_wait(&semaphore);
            send(client_socket, close_message.c_str(), close_message.size(), 0);
            // libera o recurso compartilhado
            sem_post(&semaphore);
            // fecha a conexão com o cliente
            close(client_socket);
            break;
        }
        else {
            std::string str_response(message_buffer);
            // lista usuários conectados ao servidor
            if (str_response == "list users") {
                // ENVIA ao cliente a lista de usuarios conectados
                std::string users_message = set_to_str(&users_set);
                // aguarda permissão para acessar o recurso compartilhado
                sem_wait(&semaphore);
                send(client_socket, users_message.c_str(), users_message.size(), 0);
                // libera o recurso compartilhado
                sem_post(&semaphore);
            }
            // envia uma mensagem publica para todos os usuarios conectados
            else if ((str_response.substr(0, 9) == "send all ") && (str_response.size() > 9)) {
                std::string public_msg = str_response.substr(9);
                // espera-se que as mensagens sempre sejam enviadas entre aspas, entao remove-as
                public_msg.erase(0, 1);
                public_msg.pop_back();

                // formata a mensagem para impressao
                std::string msg_all = current_time() + " " + str_user_index + ": " + public_msg;
                std::string msg_conf = current_time() + " -> all: " + public_msg;

                // imprime no terminal a mensagem
                std::cout << msg_all << std::endl;
                // envia para todos na sala
                for (std::set<int>::iterator it = sockets_set.begin(); it != sockets_set.end(); ++it) {
                    // aguarda permissão para acessar o recurso compartilhado
                    sem_wait(&semaphore);
                    if (*it != client_socket)
                        send(*it, msg_all.c_str(), msg_all.size(), 0);
                    // envia com formataçao especial para o cliente que enviou
                    if (*it == client_socket)
                        send(*it, msg_conf.c_str(), msg_conf.size(), 0);
                    // libera o recurso compartilhado
                    sem_post(&semaphore);
                }
            }
            // envia uma mensagem privada para algum usuario
            else if (str_response.substr(0, 8) == "send to ") {
                // tenta descobrir o usuario destino da mensagem
                std::string str_dest = str_response.substr(8, 2);
                int int_dest = stoi(str_dest);

                int socket_dest = -1;
                int i = 0;
                for (std::set<int>::iterator it = users_set.begin(); it != users_set.end(); ++it) {
                    if (*it == int_dest) {
                        socket_dest = *std::next(sockets_set.begin(), i);
                        break;
                    }
                    i++;
                }
                if (socket_dest == -1) {
                    std::cout << "User " << str_dest << " not found" << std::endl;
                    std::string msg_error = "Receiver not found";
                    // aguarda permissão para acessar o recurso compartilhado
                    sem_wait(&semaphore);
                    send(client_socket, msg_error.c_str(), msg_error.size(), 0);
                    // libera o recurso compartilhado
                    sem_post(&semaphore);
                    continue;
                }

                std::string private_msg = str_response.substr(11);
                // espera-se que as mensagens sempre sejam enviadas entre aspas, entao remove as aspas
                private_msg.erase(0, 1);
                private_msg.pop_back();

                // formata a mensagem para impressao
                std::string msg_send = "P " + current_time() + " " + str_user_index + ": " + private_msg;
                std::string msg_conf = "P "+ current_time() + " -> " + str_dest + ": " + private_msg;
                // aguarda permissão para acessar o recurso compartilhado
                sem_wait(&semaphore);
                // envia as mensagens
                send(socket_dest, msg_send.c_str(), msg_send.size(), 0);
                send(client_socket, msg_conf.c_str(), msg_conf.size(), 0);
                // libera o recurso compartilhado
                sem_post(&semaphore);
            }
            // caso seja digitado um comando inválido
            else {
                // ENVIA ao cliente um aviso de comando invalido
                std::string invalid_message = "Invalid command";
                // aguarda permissão para acessar o recurso compartilhado
                sem_wait(&semaphore);
                send(client_socket, invalid_message.c_str(), invalid_message.size(), 0);
                // libera o recurso compartilhado
                sem_post(&semaphore);
            }
        }
    }
    // tira do set de usuarios o cliente que vai ser fechado
    users_set.erase(user_index);
    // tira do set de sockets o cliente que vai ser fechado
    sockets_set.erase(client_socket);
    // decrementa o numero de usuarios conectados
    connected_users--;
    // ENVIA a todos os ainda conectados o aviso de que o usuario foi desconectado
    message = "User " + str_user_index + " left the group!";
    // aguarda permissão para acessar o recurso compartilhado
    sem_wait(&semaphore);
    for (std::set<int>::iterator it = sockets_set.begin(); it != sockets_set.end(); ++it)
        send(*it, message.c_str(), message.size(), 0);
    // libera o recurso compartilhado
    sem_post(&semaphore);

    // finaliza a thread
    pthread_exit(NULL);
}


int main (int argc, char *argv[]) {
    // lista de threads
    pthread_t threads[MAX_USERS];
    // inicializa o semáforo com o valor inicial
    sem_init(&semaphore, 0, 1);

    // erro de argumento(s) faltante(s)
    if (argc < 3) {
        std::cerr << "Missing arguments, correct use: " << argv[0] << " [address_type] [port]" << std::endl;
        return 1;
    }

    // salva o tipo de endereco e a porta recebidos
    std::string address_type = argv[1];
    std::string port_str = argv[2];
    int port_int = std::stoi(port_str);

    // se o tipo desejado e o ipv6
    if (address_type == "v6"){
        // cria o SOCKET do servidor
        // AF_INET6 - familia de protocolos; SOCK_STREAM - tipo do socket - TCP
        int server_socket = socket(AF_INET6, SOCK_STREAM, 0);
        if (server_socket == -1) {
            std::cerr << "Error while creating server socket" << std::endl;
            return 1;
        }

        // configurar o endereco do servidor
        struct sockaddr_in6 server_address{};
        server_address.sin6_family = AF_INET6;
        server_address.sin6_port = htons(port_int);
        server_address.sin6_addr = in6addr_any;

        // VINCULA o socket ao endereco do servidor
        if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
            std::cerr << "Error while binding socket" << std::endl;
            return 1;
        }

        // ESCUTA por conexões de clientes
        if (listen(server_socket, 1) == -1) {
            std::cerr << "Error while listening for connections" << std::endl;
            return 1;
        }

        std::cout << "Server listening on port " << port_int << std::endl;

        while (1) {
            // ACEITA a conexão do cliente
            struct sockaddr_in6 client_address{};
            socklen_t client_address_size = sizeof(client_address);
            int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_size);
            if (client_socket == -1) {
                std::cerr << "Error while accepting client connection" << std::endl;
                continue;
            }
            if (connected_users >= MAX_USERS) {
                // ENVIA ao cliente o aviso de sala cheia
                std::string close_message = "User limit exceeded";
                send(client_socket, close_message.c_str(), close_message.size(), 0);
                // fecha a conexão com o cliente
                close(client_socket);
                continue;
            }

            // cria uma thread para tratar o cliente na função client_handler
            pthread_create(&threads[connected_users - 1], 0, &client_handler, (void*) &client_socket);
        }

        // FECHA o socket do servidor
        close(server_socket);
    }


    // se o tipo desejado e o ipv4
    else if (address_type == "v4"){
        // cria o SOCKET do servidor
        // AF_INET - familia de protocolos; SOCK_STREAM - tipo do socket - TCP
        int server_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (server_socket == -1) {
            std::cerr << "Error while creating server socket" << std::endl;
            return 1;
        }

        // configurar o endereco do servidor
        struct sockaddr_in server_address{};
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(port_int);
        server_address.sin_addr.s_addr = INADDR_ANY;

        // VINCULA o socket ao endereco do servidor
        if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
            std::cerr << "Error while binding socket" << std::endl;
            return 1;
        }

        // ESCUTA por conexões de clientes
        if (listen(server_socket, 1) == -1) {
            std::cerr << "Error while listening for connections" << std::endl;
            return 1;
        }

        std::cout << "Server listening on port " << port_int << std::endl;

        while (1) {
            // ACEITA a conexão do cliente
            struct sockaddr_in client_address{};
            socklen_t client_address_size = sizeof(client_address);
            int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_size);
            if (client_socket == -1) {
                std::cerr << "Error while accepting client connection" << std::endl;
                continue;
            }
            if (connected_users >= MAX_USERS) {
                // ENVIA ao cliente o aviso de sala cheia
                std::string close_message = "User limit exceeded";
                send(client_socket, close_message.c_str(), close_message.size(), 0);
                // fecha a conexão com o cliente
                close(client_socket);
                continue;
            }
            
            // cria uma thread para tratar o cliente na função client_handler
            pthread_create(&threads[connected_users - 1], 0, &client_handler, (void*) &client_socket);
        }

        // FECHA o socket do servidor
        close(server_socket);
        // destroi o semaforo
        sem_destroy(&semaphore);
        // fecha possiveis threads abertas
        pthread_exit(NULL);
    }

    return 0;
}
