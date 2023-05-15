//---------------------------------------------------------------------
// Arquivo	: main.cpp
// Conteudo	: programa de operação do escalonador de urls
// Autor	: Erick Sunclair (ericksunclair@ufmg.br)
// Data     : 28/11/2021
//---------------------------------------------------------------------

#include <string>
#include <iostream>
#include <fstream>
#include "item_url.h"
#include "lista_urls.h"

using namespace std;

int main(int argc, char * argv[]){
    // abrindo o arquivo de entrada de comandos
    ifstream arq_in;
    arq_in.open(argv[1]);
    
    // criando nome para o arquivo de saida
    string nome_arq_out;
    nome_arq_out = argv[1];
    nome_arq_out.erase(nome_arq_out.end()-4, nome_arq_out.end());
    nome_arq_out += "-out.txt";
    nome_arq_out = "result/" + nome_arq_out;
    // abrindo arquivo de saida dos resultados
    ofstream arq_out;
    arq_out.open(nome_arq_out);
    
    // essas strings vao receber as palavras do arq_in
    string word;
    string quantity;
    string host;

    // incializa uma classe lista_urls
    lista_urls *ListaUrls = new lista_urls;

    // teste se os arquivos foram abertos
    if(!arq_in.is_open()){
        cout << "Não foi possível abrir o arquivo de entrada" << endl;
        return EXIT_FAILURE;
    }
    else if(!arq_out.is_open()){
        cout << "Não foi possível abrir o arquivo de saída" << endl;
        return EXIT_FAILURE;
    }
    // realiza os comandos descritos no arquivo
    else{
        while(!arq_in.eof()){
            try{
                arq_in >> word;
                if(word == "ADD_URLS"){
                    arq_in >> quantity;
                    ListaUrls->add_urls(arq_in, stoi(quantity));
                }
                else if(word == "ESCALONA_TUDO"){
                    ListaUrls->escalona_tudo(arq_out);
                }
                else if(word == "ESCALONA"){
                    arq_in >> quantity;
                    ListaUrls->escalona(arq_out, stoi(quantity));
                }
                else if(word == "ESCALONA_HOST"){
                    arq_in >> host;
                    arq_in >> quantity;
                    ListaUrls->escalona_host(arq_out, host, stoi(quantity));
                }
                else if(word == "VER_HOST"){
                    arq_in >> host;
                    ListaUrls->ver_host(arq_out, host);
                }
                else if(word == "LISTA_HOSTS"){
                    ListaUrls->lista_hosts(arq_out);
                }
                else if(word == "LIMPA_HOST"){
                    arq_in >> host;
                    ListaUrls->limpa_host(host);
                }
                else if(word == "LIMPA_TUDO"){
                    ListaUrls->limpa_tudo();
                }
                // caso seja lido um comando não reconhecido
                else{
                    // fecha os arquivos
                    arq_in.close();
                    arq_out.close();
                    // imprime mensagem de erro e para o programa
                    cout << "Comando não reconhecido: " << word << endl;
                    return EXIT_FAILURE;
                }
            }catch(const char *e){
                cout << e << endl;
                return EXIT_FAILURE;
            }
        }
    }

    // fecha os arquivos
    delete ListaUrls;
    arq_in.close();
    arq_out.close();
    return 0;
}