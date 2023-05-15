//---------------------------------------------------------------------
// Arquivo	: item_url.cpp
// Conteudo	: implementacao do tipo item_url da nossa lista encadeada de urls 
// Autor	: Erick Sunclair (ericksunclair@ufmg.br)
// Data     : 28/11/2021
//---------------------------------------------------------------------

#include <string>
#include <iostream>
#include <fstream>
#include "item_url.h"

using namespace std;

item_url::item_url()
// Descricao: construtor da classe item_url
// Entrada: nao tem
// Saida: nao tem
{
    host = "";
    url = "";
    proximo = NULL;
}

