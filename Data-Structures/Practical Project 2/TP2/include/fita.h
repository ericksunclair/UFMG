//---------------------------------------------------------------------
// Arquivo	: fita.h
// Conteudo	: definições do tipo fita (uma lista de entidades)
// Autor	: Erick Sunclair (ericksunclair@ufmg.br)
// Data     : 12/01/2021
//---------------------------------------------------------------------

#ifndef FITA
#define FITA

#include <string>
#include <iostream>
#include <fstream>
#include "entidade.h"

using namespace std;

// tipo que vai representar cada fita
class fita{
    private:
        // numero de entidades na fita
        int num_entidades;
        // lista encadeada de entidades
        entidade *Entidades = new entidade;
        
    public:
        // construtor da classe fita
        fita(const int &_num_entidades);

        // outros métodos:
        // salva na fita atual num_entidades entidades do arq_in (ou ate o arq_in acabar)
        void le_entidades(ifstream &arq_in);
        // ordena as entidades (usando quicksort) - maior num de acessos primeiro
        void ordena_entidades();
        // implementaçao da etapa de ordenação do quicksort
        void ordena(int esq, int dir, entidade *ents);
        // implementaçao da etapa de partição do quicksort
        void particao(int esq, int dir, int *i, int *j, entidade *ents);
        // escreve as entidades ordenadas no arquivo de saída da rodada
        void escreve_entidades(const string &nome_arq) const;

};


#endif