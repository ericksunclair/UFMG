//---------------------------------------------------------------------
// Arquivo	: server.cpp
// Conteudo	: programa de um servidor para comunicação socket
// Autor	: Erick Sunclair (ericksunclair@ufmg.br)
// Data     : 14/05/2023
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

// funcao para avaliar se o arquivo tem extensao valida
bool is_valid_extension(const std::string& filename) {
    // extensoes validas
    std::string valid_extensions[] = {".txt", ".c", ".cpp", ".py", ".tex", ".java"};

    // se o arquivo nao tem extensao, retorna falso
    if (filename.find_last_of(".") == std::string::npos) {
        return false;
    } 
    // se ele tem extensao, salva essa extensao
    std::string file_extension = filename.substr(filename.find_last_of("."));

    // checa se a extensao do arquivo e uma das extensoes validas
    for (const std::string& extension : valid_extensions) {
        if (file_extension == extension) {
            return true;
        }
    }
    
    // se a extensao do arquivo nao e uma das extensoes validas
    return false;
}


int main(int argc, char *argv[]) {
    // erro de argumento(s) faltante(s)
    if (argc < 3) {
        std::cerr << "missing arguments, correct use: " << argv[0] << " [IPaddress] [port]" << std::endl;
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
        std::cerr << "error while creating client socket" << std::endl;
        return 1;
    }

    // cria estrutura de enderecamento de rede para o servidor
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;            // familia do endereco
    server_address.sin_port = htons(port_int);          // porta do endereco no formato "network short"
    // converte o endereco IP (string) para uma estrutura de endereco de rede da familia AF_INET
    // e salva no server_address.sin_addr, ja tratando possivel erro de endereço IP invalido
    if (inet_pton(AF_INET, ip_address.c_str(), &(server_address.sin_addr)) <= 0) {          // endereco
        std::cerr << "invalid IP address" << std::endl;
        return 1;
    }
    // obs: usei AF_INET (IPv4) porque muitos servidores ainda são configurados para suportar apenas IPv4,
    // mas assim o cliente ainda é capaz de se conectar a servidores IPv6 se eles suportarem ambos os protocolos

    // CONECTA o socket do cliente ao endereco do servidor
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        std::cerr << "error while connecting to server" << std::endl;
        return 1;
    }

    std::cout << "connected to server" << std::endl;

    // string para salvar o nome do arquivo selecionado
    std::string selected_file;

    // loop principal do cliente
    while (1) {
        // espera pelo comando do usuario
        std::string command;
        std::cout << "type a command: ";
        std::getline(std::cin, command);

        // encerra a conexao se foi solicitado pelo usuario
        if (command == "exit") {
            // Envia a mensagem para o servidor
            if (send(client_socket, command.c_str(), command.size(), 0) == -1) {
                std::cerr << "error while sending exit message to server" << std::endl;
                close(client_socket);
                return 1;
            }
            break;
        }

        // comando para selecionar arquivo
        else if (command.substr(0, 11) == "select file") {
            // extrai o nome do arquivo
            std::string arquivo = command.substr(12);

            // verifica se a extensão do arquivo e valida
            if (!is_valid_extension(arquivo)) {
                std::cerr << arquivo << " not valid!" << std::endl;
                continue;
            }

            // verifica se o arquivo existe
            std::ifstream file_stream(arquivo);
            if (!file_stream.is_open()) {
                std::cerr << arquivo << " do not exist" << std::endl;
                continue;
            }

            // armazena o nome do arquivo selecionado
            selected_file = arquivo;
            std::cout << selected_file << " selected" << std::endl;
            file_stream.close();
        } 
        
        // comando para enviar arquivo
        else if (command == "send file") {
            // verifica se um arquivo foi selecionado
            if (selected_file.empty()) {
                std::cerr << "no file selected!" << std::endl;
                continue;
            }

            // abre o arquivo para leitura
            std::ifstream file_stream(selected_file, std::ios::binary);
            if (!file_stream) {
                std::cerr << "error while opening the selected file" << std::endl;
                continue;
            }

            // verifica se o arquivo tem no máximo 500 bytes
            file_stream.seekg(0, std::ios::end);
            std::streampos file_size = file_stream.tellg();
            file_stream.seekg(0, std::ios::beg);

            if (file_size > 500) {
                std::cerr << "file too big, maximum size allowed: 500 bytes" << std::endl;
                file_stream.close();
                continue;
            }

            // le o conteudo do arquivo
            std::string file_content((std::istreambuf_iterator<char>(file_stream)), std::istreambuf_iterator<char>());

            // formata a mensagem com o cabeçalho
            std::string message = selected_file + '\n' + file_content;
            
            // ENVIA a mensagem para o servidor
            if (send(client_socket, message.c_str(), message.length(), 0) == -1) {
                std::cerr << "error while sending the selected file" << std::endl;
            }

            // fecha o arquivo
            file_stream.close();
            std::cout << "file " << selected_file << " sent" << std::endl;
            break;
        } 
        
        // caso seja digitado um comando inválido
        else {
            std::cout << "invalid command" << std::endl;
        }
    }

    // RECEBE a resposta do servidor
    char response[BUFSZ];
    std::memset(response, 0, sizeof(response));         // limpa espaço da memoria (buffer)
    int bytes_read = recv(client_socket, response, sizeof(response), 0);
    if (bytes_read == -1) {
        std::cerr << "error while receiving answer from the server" << std::endl;
        return 1;
    }

    std::cout << response << std::endl;

    // FECHA a conexão com o servidor
    close(client_socket);

    return 0;
}
