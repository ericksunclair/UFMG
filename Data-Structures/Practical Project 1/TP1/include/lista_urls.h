//---------------------------------------------------------------------
// Arquivo	: lista_urls.h
// Conteudo	: definicoes da lista escalonada de urls
// Autor	: Erick Sunclair (ericksunclair@ufmg.br)
// Data     : 28/11/2021
//---------------------------------------------------------------------

#ifndef LISTA_URLS
#define LISTA_URLS

#include <string>
#include <iostream>
#include <fstream>
#include "item_url.h"

using namespace std;

class lista_urls{
    private:
        // cabeça e cauda da lista encadeada
        item_url *primeiro;
        item_url *ultimo;
        // numero de membros da lista
        int tamanho;
        
    public:
        // construtor e destrutor da classe lista_urls
        lista_urls();
        ~lista_urls();

        // outro métodos:
        // adiciona à lista_urls as urls informadas nas linhas seguintes
        void add_urls(ifstream &arq_in, int quant);
        // escalona todas as urls
        void escalona_tudo(ofstream &arq_out);
        // escalona uma quantidade especifica de urls
        void escalona(ofstream &arq_out, int quant);
        // escalona certa quantidade de urls apenas de um host especifico
        void escalona_host(ofstream &arq_out, string host, int quant);
        // exibe todas as urls em um host especifico, na ordem de prioridade
        void ver_host(ofstream &arq_out, string host);
        // exibe todos os hosts seguindo a ordem em que foram conhecidos
        void lista_hosts(ofstream &arq_out);
        // limpa a lista de urls de um host
        void limpa_host(string host);
        // limpa todas as urls, inclusive os hosts
        void limpa_tudo();

        // essas funções vão fazer o tratamento dos endereços recebidos pelo arquivo
        // retira "/" ao fim do endereço, "www.", "#<...>"
        string condiciona_url(string url);
        // retira "/" ao fim do endereço, "www.", "#<...>" e "http://"
        string condiciona_host(string host);
        // retorna apenas o host de uma url
        string get_host(string url);
        // confirma se o url recebido é compativel para ser usado em nossa lista
        // (seu protocolo deve ser HTTP e a página deve ser HTML)
        bool checar_consistencia(string url);
};

#endif