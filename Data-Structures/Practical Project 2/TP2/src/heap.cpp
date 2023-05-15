//---------------------------------------------------------------------
// Arquivo	: heap.cpp
// Conteudo	: implementação do tipo heap
// Autor	: Erick Sunclair (ericksunclair@ufmg.br)
// Data     : 12/01/2021
//---------------------------------------------------------------------

#include <string>
#include <iostream>
#include <fstream>
#include "heap.h"

using namespace std;

heap::heap(const int &num_fitas)
// Descricao: construtor da classe heap
// Entrada: nao tem
// Saida: nao tem
{
    // inicializa a lista encadeada com o tamanho especificado
    Entidades = (entidade *)calloc(num_fitas, sizeof(entidade));
    num_entidades_atual = 0;
}

int heap::adiciona(const entidade &Entidade)
// Descricao: adiciona ao heap uma entidade 
// Entrada: Entidade - entidade a ser adicionada
// Saida: nao tem
{
    // inserimos essa nova entidade no fim da lista
    Entidades[num_entidades_atual] = Entidade;
    num_entidades_atual++;
    
    return 0;
}

void heap::ordena_entidades()
// Descricao: ordena as entidades (usando quicksort) - maior num de acessos primeiro
// Entrada: nao tem
// Saida: nao tem
{
    // chama o metodo de ordenação para a lista de Entidades (a fita)
    ordena(0, num_entidades_atual-1, Entidades);
}

void heap::ordena(int esq, int dir, entidade *ents)
// Descricao: implementaçao da etapa de ordenação do quicksort, ou seja,
// chama a particao para cada subconjunto ja particionado
// Entrada: esq - indice inicial da fita
//          dir - indice final da fita
//          ents - fita a ser organizada
// Saida: nao tem
{
    // indices para percorrer a fita
    int i, j;
    // chama o metodo de partiçao para o intervalo designado
    particao(esq, dir, &i, &j, ents);
    // se j nao chegou ao limite esquerdo chamo recursivamente o metodo
    // ordena para o intervalo da esquerda
    if(esq < j) ordena(esq, j, ents);
    // se o i nao chegou ao limite direito chamo recursivamente o metodo 
    // ordena para o intervalo da direita
    if(i < dir) ordena(i, dir, ents);
}

void heap::particao(int esq, int dir, int *i, int *j, entidade *ents)
// Descricao: implementaçao da etapa de partição do quicksort, ou seja,
// escolhe um pivo e posiciona os elementoss menores que ele de um lado
// e os maiores de outro
// Entrada: esq - indice inicial da fita
//          dir - indice final da fita
//          i e j - indices que vao percorrer a fita
//          ents - fita a ser organizada
// Saida: nao tem
{
    // entidades auxiliares
    entidade x, w;
    // incializa os indices com os limites da fita
    *i = esq; *j = dir;
    // inicializa o pivo como o elemento central da fita
    x = ents[(*i + *j)/2];
    // até os indices se cruzarem
    do{
        // encontro o primeiro valor maior que o pivo vindo da esquerda
        while(x.get_num_acessos() > ents[*i].get_num_acessos()) (*i)++;
        // encontro o primeiro valor menor que o pivo vindo da direita
        while(x.get_num_acessos() < ents[*j].get_num_acessos()) (*j)--;
        // se os indices i e j nao se cruzaram
        if(*i <= *j){
            // troco os itens apontados por i e j de lugar
            w = ents[*i]; ents[*i] = ents[*j]; ents[*j] = w;
            // incremento (ou decremento) os indices
            (*i)++; (*j)--;
        }
    } while (*i <= *j);
}

entidade heap::retira()
// Descricao: retiro a primeira entidade do heap (a de maior num de acessos)
// Entrada: nao tem
// Saida: ponteiro para a entidade retirada do heap
{
    // salva em uma entidade temporaria a entidade a ser retornada
    entidade ent_retorno;
    ent_retorno = Entidades[0];
    // desloca todas as entidades para a esquerda e decrementa o numero de elementos
    for(int i=0; i<num_entidades_atual-1; i++){
        Entidades[i].set_url(Entidades[i+1].get_url());
        Entidades[i].set_num_acessos(Entidades[i+1].get_num_acessos());
        Entidades[i].set_ind_rodada(Entidades[i+1].get_ind_rodada());
    }
    num_entidades_atual--;
    // retorna a entidade salva no inicio
    return ent_retorno;
}