//---------------------------------------------------------------------
// Arquivo	: item_url.h
// Conteudo	: definicoes do tipo item_url da nossa lista encadeada de urls
// Autor	: Erick Sunclair (ericksunclair@ufmg.br)
// Data     : 28/11/2021
//---------------------------------------------------------------------

#ifndef ITEM_URL
#define ITEM_URL

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// tipo que vai representar cada url (cada célula) da lista encadeada
class item_url{
    private:
        string host;            // host do url 
        string url;             // url
        item_url *proximo;      // próximo url da lista encadeada

    public:
        // construtor da classe item_url
        item_url();

    friend class lista_urls;
};


#endif