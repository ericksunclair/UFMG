//---------------------------------------------------------------------
// Arquivo	: hash.h
// Conteudo	: definições do tipo hash (nosso indice invertido)
// Autor	: Erick Sunclair (ericksunclair@ufmg.br)
// Data     : 14/02/2022
//---------------------------------------------------------------------

#ifndef HASH
#define HASH

#include <string>
#include <iostream>
#include <fstream>
#include <utility>

using namespace std;

struct linha{
    // termo
    string termo;
    // hash value
    double hash;
    // numero de ocorrencias ja registradas para este termo
    int ocor;
    // lista encadeada de ocorrencias para representar todas as ocorrencias do termo
    pair<int, int>* ocorrencias;    // first = id do documento, second = freq do termo no documento
};

// tipo que vai representar um heap de entidades
class Hash{
    private:
        // num atual de entidades no heap
        int num_termos;
        // numero de termos ja prenchidos por alguma ocorrencia
        int num_termos_preenchidos;
        // lista encadeada de linhas que vai representar nossa tabela hash
        struct linha *tabela;
        
    public:
        // construtor da classe heap
        Hash(const int &num_palavras_unicas);
        // destrutor da classe Hash
        ~Hash();

        // outros métodos:
        // adiciona uma ocorrencia
        void add(const string &termo, const int &doc_id, const int &freq_termo_doc);
        // calcula o hash de um termo
        long long compute_hash(string const& s);
        // retorna o i-ésimo termo do hash
        string get_termo(const int &i);
        // retorna o hash value do i-ésimo termo do hash
        double get_hash(const int &i);
        // retorna a frequencia de um termo em um documento
        int freq_termo_doc(const string &termo, const int &doc_id);
        // retorna o numero de documentos que tem o termo
        int quantos_docs_tem(const string &termo);

};

#endif