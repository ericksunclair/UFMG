//---------------------------------------------------------------------
// Arquivo	: fita.cpp
// Conteudo	: implementação do tipo fita (uma lista de entidades)
// Autor	: Erick Sunclair (ericksunclair@ufmg.br)
// Data     : 12/01/2021
//---------------------------------------------------------------------

#include <string>
#include <iostream>
#include <fstream>
#include "fita.h"

using namespace std;

fita::fita(const int &_num_entidades)
// Descricao: construtor da classe fita
// Entrada: nao tem
// Saida: nao tem
{
    // inicializa a lista encadeada com o tamanho especificado
    num_entidades = _num_entidades;
    Entidades = (entidade *)calloc(num_entidades, sizeof(entidade));
}

void fita::le_entidades(ifstream &arq_in)
// Descricao: salva na fita atual num_entidades entidades do arq_in (ou ate o arq_in acabar)
// Entrada: arq_in - arquivo de entrada para leitura
// Saida: nao tem
{
    // para cada entidade da fita
    for(int i=0; i<num_entidades; i++){
        // se o arquivo acabar
        if(arq_in.eof()){
            // muda o numero de entidades dessa fita
            num_entidades = i;
            // sai da função
            return;
        }

        // salva a url na entidade
        string url;
        arq_in >> url;
        Entidades[i].set_url(url);
        // salva o numero de acessos na entidade
        int num_acessos;
        arq_in >> num_acessos;
        Entidades[i].set_num_acessos(num_acessos);
    }
}

void fita::ordena_entidades()
// Descricao: ordena as entidades (usando quicksort) - maior num de acessos primeiro
// Entrada: nao tem
// Saida: nao tem
{
    // chama o metodo de ordenação para a lista de Entidades (a fita)
    ordena(0, num_entidades-1, Entidades);
}

void fita::ordena(int esq, int dir, entidade *ents)
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

void fita::particao(int esq, int dir, int *i, int *j, entidade *ents)
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

void fita::escreve_entidades(const string &nome_arq) const
// Descricao: escreve as entidades ordenadas no arquivo de saída da rodada
// Entrada: nome_arq - string com nome do arquivo no qual devemos escrever as entidades
// Saida: nao tem
{
    // abre o arquivo de saida
    ofstream arq_out;
    arq_out.open(nome_arq);
    // para cada entidade da fita
    for(int i=0; i<num_entidades; i++){
        // escreve a url e o seu numero de acessos
        arq_out << Entidades[i].get_url() << " " << Entidades[i].get_num_acessos();
        if(i != num_entidades-1) arq_out << endl;
    }
}