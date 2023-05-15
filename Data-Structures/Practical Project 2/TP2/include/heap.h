//---------------------------------------------------------------------
// Arquivo	: heap.h
// Conteudo	: definições do tipo heap
// Autor	: Erick Sunclair (ericksunclair@ufmg.br)
// Data     : 12/01/2021
//---------------------------------------------------------------------

#ifndef HEAP
#define HEAP

#include <string>
#include <iostream>
#include <fstream>
#include "entidade.h"

using namespace std;

// tipo que vai representar um heap de entidades
class heap{
    private:
        // num atual de entidades no heap
        int num_entidades_atual;
        // lista encadeada de entidades
        entidade *Entidades = new entidade;
        
    public:
        // construtor da classe heap
        heap(const int &num_fitas);

        // outros métodos:
        // adiciona ao heap uma entidade
        int adiciona(const entidade &Entidade);
        // ordena as entidades (usando quicksort) - maior num de acessos primeiro
        void ordena_entidades();
        // implementaçao da etapa de ordenação do quicksort
        void ordena(int esq, int dir, entidade *ents);
        // implementaçao da etapa de partição do quicksort
        void particao(int esq, int dir, int *i, int *j, entidade *ents);
        // testa se o heap está vazio
        int get_tamanho() const{ return num_entidades_atual; };
        // retiro a primeira entidade do heap (a de maior num de acessos)
        entidade retira();

};

#endif