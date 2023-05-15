//---------------------------------------------------------------------
// Arquivo	: hash.cpp
// Conteudo	: definições do tipo hash (nosso indice invertido)
// Autor	: Erick Sunclair (ericksunclair@ufmg.br)
// Data     : 14/02/2022
//---------------------------------------------------------------------

#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include "hash.h"

using namespace std;

Hash::Hash(const int &num_palavras_unicas)
// Descricao: construtor da classe hash
// Entrada: numero de termos do hash (numero de palavras unicas)
// Saida: nao tem
{
    num_termos = num_palavras_unicas;
    num_termos_preenchidos = 0;
    tabela = (struct linha*) calloc(num_termos, sizeof(struct linha));
    for(int i=0; i<num_termos; i++){
        tabela[i].ocor = 0;
        tabela[i].ocorrencias = (pair<int, int>*) calloc(tabela[i].ocor, sizeof(pair<int, int>));
    }
}


Hash::~Hash()
// Descricao: destrutor da classe hash
// Entrada: nao tem
// Saida: nao tem
{
    // liberando as variaveis alocadas dinamicamente
    for(int i=0; i<num_termos; i++){
        free(tabela[i].ocorrencias);
    }
    free(tabela);
}


void Hash::add(const string &termo, const int &doc_id, const int &freq_termo_doc)
// Descricao: adiciona uma ocorrencia ao hash
// Entrada: termo - termo do qual é a ocorrencia
//          doc_id - id do documento
//          freq_termo_doc - quantas vezes o termo ocorreu no documento
// Saida: nao tem
{
    long long hash_value = compute_hash(termo);     // valor hash do termo a ser inserido
    int encontrou_termo = 0;        // flag para sinalizar que o termo ja foi encontrado no hash e inserido
    // caso 1: o termo ja possui ocorrencias registradas - a nova ocorrencia é inserida
    for(int i=0; i<num_termos_preenchidos; i++){
        if(compute_hash(tabela[i].termo) == hash_value){
            tabela[i].ocor += 1;
            tabela[i].ocorrencias = (pair<int, int>*) realloc(tabela[i].ocorrencias, tabela[i].ocor*sizeof(pair<int, int>));
            tabela[i].ocorrencias[tabela[i].ocor-1].first = doc_id;
            tabela[i].ocorrencias[tabela[i].ocor-1].second = freq_termo_doc;
            encontrou_termo = 1;
            break;
        }
    }
    // caso 2: o termo nao possui ocorrencias registradas - uma nova linha do hash e preenchida por este termo e sua ocorrencia e inserida
    if(encontrou_termo == 0){
        tabela[num_termos_preenchidos].termo = termo;
        tabela[num_termos_preenchidos].hash = hash_value;
        tabela[num_termos_preenchidos].ocor = 1;
        tabela[num_termos_preenchidos].ocorrencias = (pair<int, int>*) realloc(tabela[num_termos_preenchidos].ocorrencias, tabela[num_termos_preenchidos].ocor*sizeof(pair<int, int>));
        tabela[num_termos_preenchidos].ocorrencias[tabela[num_termos_preenchidos].ocor-1].first = doc_id;
        tabela[num_termos_preenchidos].ocorrencias[tabela[num_termos_preenchidos].ocor-1].second = freq_termo_doc;
        num_termos_preenchidos += 1;
    }
}


long long Hash::compute_hash(string const& s)
// Descricao: adiciona uma ocorrencia ao hash
// Entrada: termo - termo do qual é a ocorrencia
// Saida: valor hash do termo
{
    const int p = 31;
    const int m = 1e9 + 9;
    long long hash_value = 0;
    long long p_pow = 1;
    for (auto it=s.begin(); it!=s.end(); it++) {
        hash_value = (hash_value + (*it - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}


string Hash::get_termo(const int &i)
// Descricao: retorna o i-ésimo termo do hash
// Entrada: i - posição do termo que queremos
// Saida: string com o termo
{
    if (i > num_termos) return "";
    return tabela[i].termo;
}


double Hash::get_hash(const int &i)
// Descricao: retorna o hash value do i-ésimo termo do hash
// Entrada: i - posição do termo que queremos
// Saida: double com o hash value
{
    if (i > num_termos) return -1;
    return tabela[i].hash;
}


int Hash::freq_termo_doc(const string &termo, const int &doc_id)
// Descricao: retorna a frequencia de um termo em um documento
// Entrada: termo - termo do qual querermos a frequencia
//          doc_id - id do documento
// Saida: inteiro com o numero de ocorrencias do termo no documento
{
    // procura o termo na tabela
    for(int i=0; i<num_termos; i++){
        if(tabela[i].termo == termo){
            // procurao documento desejado nesse termo
            for(int j=0; j<tabela[i].ocor; j++){
                if(tabela[i].ocorrencias[j].first == doc_id){
                    // retorna a frequencia desse termo nesse documento
                    return tabela[i].ocorrencias[j].second;
                }
            }
        }
    }
    // retorna 0 se nao foi encontrada nenhuma ocorrencia desse termo nesse documento
    return 0;
}


int Hash::quantos_docs_tem(const string &termo)
// Descricao: retorna o numero de documentos que tem o termo
// Entrada: termo - termo a ser procurado
// Saida: inteiro com o numero de documentos que possuem o termo
{
    // percorre a tabela procurando o termo e retorna quantas ocorrencias ele tem
    for(int i=0; i<num_termos; i++){
        if(tabela[i].termo == termo){
            return tabela[i].ocor;
        }
    }
    // se nao foi achado nenhum documento com esse termo retorna 0
    return 0;
}