//---------------------------------------------------------------------
// Arquivo	: main.cpp
// Conteudo	: Indexador em Memória e Processador de Consultas
// Autor	: Erick Sunclair (ericksunclair@ufmg.br)
// Data     : 14/02/2022
//---------------------------------------------------------------------

#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cmath>
#include <math.h>
#include "hash.h"

using namespace std;
const int num_max_palavras = 27000;        // maximo de palavras unicas que o sistema pode armazenar
const int num_max_palavras_consulta = 100;    // maximo de palavras do documento de consulta

int main(int argc, char * argv[]){

    int num_total_docs = 0;         // numero total de documentos
    int num_total_palavras = 0;         // numero total de palavras
    int num_palavras_unicas = 0;        // numero de palavras unicas

    // SALVA AS STOPWORDS
    // abrindo o arquivo que possui as stopwords a serem desconsideradas
    ifstream arq_stopwords;
    arq_stopwords.open(argv[8]);
    // testa se o arquivo foi aberto
    if(!arq_stopwords.is_open()){
        cout << "Não foi possível abrir o arquivo de stopwords!" << endl;
        return EXIT_FAILURE;
    }
    // cria um vetor com as stopwords
    int num_sw = 0;     // numero de stopwords no arquivo
    string word;
    // conta as stopwords
    while(!arq_stopwords.eof()){
        arq_stopwords >> word;
        num_sw++;
    }
    string stopwords[num_sw];       // vetor com tamanho correto para salvar as stopwords
    arq_stopwords.clear();
    arq_stopwords.seekg(0);     // reposiciona o ponteiro de leitura do arquivo para o inicio
    int i = 0;
    // salva as stopword no vetor criado
    while(!arq_stopwords.eof()){
        arq_stopwords >> stopwords[i];
        i++;
    }
    arq_stopwords.close();



    // TRATA OS DOCUMENTOS
    // percorre todos os documentos do corpus tratando esses documentos
    string corpus_name = argv[6];       // string com o nome do diretorio dos documentos (corpus)
    string original_corpus_path = corpus_name + "/";     // caminho para o corpus original
    string new_corpus_path = "corpus_tratado/";     // caminho para o novo corpus
    for(const auto & file : filesystem::directory_iterator(original_corpus_path)){
        // cria um novo diretorio e salva todos os documentos do corpus apos tratamento
        // (são retirados pontos, "/n", todo o texto é passado para lowercase
        // e sao ignoradas stopwords e palavras)
        ifstream arq_documento;     // documento original
        arq_documento.open(file.path());
        string filename = filesystem::path(file.path()).filename().string();    // nome do doc original
        // testa se o arquivo foi aberto
        if(!arq_documento.is_open()){
            cout << "Não foi possível abrir o documento" << filename << endl;
            return EXIT_FAILURE;
        }

        ofstream arq_new_doc;       // documento tratado
        arq_new_doc.open(new_corpus_path + filename);
        // testa se o arquivo foi aberto
        if(!arq_new_doc.is_open()){
            arq_documento.close();
            cout << "Não foi possível abrir o NOVO documento" << filename << endl;
            return EXIT_FAILURE;
        }

        arq_documento >> word;      // string para receber palavras
        int desconsiderar=0;        // flag para desconsiderar uma palavra
        // tratamento dos documentos
        while(!arq_documento.eof()){
            // se a palavra tem simbolos eles sao substituidos por espaços em branco
            for(unsigned int i=0; i<word.size(); i++){
                if((word[i]=='\\') && (word[i+1]=='n')){
                    word[i] = ' ';
                    word[i+1] = ' ';
                }
                if(((word[i]<=47 && word[i]>=33) || (word[i]>=58 && word[i]<=64) ||
                    (word[i]>=91 && word[i]<=96) || word[i]>=123)){
                        word[i] = ' ';
                }
            }

            // a palavra é passada para caixa baixa
            for(unsigned int i=0; i<word.size(); i++){
                word[i] = tolower(word[i]);
            }

            string word_completa = word + " ";      // palavra atual
            string word_separada;       // parte da palavra que vai até o espaço
            // vai dividindo a palavra em seus espaços e imprimindo cada parte
            // caso essa parte não seja uma stopword nem possua numeros
            while(word_completa.size() > 0){
                for(unsigned int i=0; i<word_completa.size(); i++){      // loop para procurar espaços
                    if(word_completa[i] == ' '){
                        word_separada = word_completa.substr(0, i);
                        word_completa.erase(0, i+1);
                        // se a palavra separada tem algum numero ela é desconsiderada
                        for(unsigned int j=0; j<word_separada.size(); j++){
                            if(word_separada[j]>=48 && word_separada[j]<=57){
                                desconsiderar = 1;
                                break;
                            }
                        }
                        // if((word_separada == " ") && desconsiderar==0) desconsiderar=1;
                        // se a palavra separada é uma stopword ela é desconsiderada
                        if(desconsiderar == 0){
                            for(int j=0; j<num_sw; j++){
                                if(word_separada == stopwords[j]){
                                    desconsiderar = 1;
                                    break;
                                }
                            }
                        }
                        // se o flag nao desconsidera a palavra ela é impressa no novo documento
                        if(desconsiderar == 0){
                            arq_new_doc << word_separada << " ";
                        }
                        else desconsiderar = 0;
                        break;      // sai do loop de procura de espaços (já encontrou)
                    }
                }
            }
            arq_documento >> word;
        }
        arq_documento.close();
        arq_new_doc.close();
    }



    // CONTA AS PALAVRAS E DOCUMENTOS
    string palavras_unicas[num_max_palavras];      // lista de palavras unicas
    int *lista_docs = (int*) calloc(num_total_docs, sizeof(int));
    // percorre os documentos tratados contando as palavras e os documentos
    for(const auto & file : filesystem::directory_iterator(new_corpus_path)){
        string filename = filesystem::path(file.path()).filename().string();    // nome do doc tratado
        ifstream arq_new_doc;       // documento tratado
        arq_new_doc.open(new_corpus_path + filename);
        // testa se o arquivo foi aberto
        if(!arq_new_doc.is_open()){
            cout << "Não foi possível abrir o NOVO documento" << filename << endl;
            return EXIT_FAILURE;
        }

        string id_doc_string = filename;
        id_doc_string.erase(id_doc_string.end()-4, id_doc_string.end());
        int id_doc = stoi(id_doc_string);       // id do documento
        arq_new_doc >> word;        // leitura da palavra
        int encontrou_palavra = 0;      // flag para sinalizar se encontrar a palavra na lista
        // percorre o documento salvando as ocorrencias das palavras
        while(!arq_new_doc.eof()){
            // caso 1: a palavra ja existe na lista
            for(int i=0; i<num_palavras_unicas; i++){
                if(palavras_unicas[i] == word){
                    encontrou_palavra = 1;
                    break;
                }
            }
            // caso 2: a palavra nao existe na lista
            if(encontrou_palavra == 0){
                num_palavras_unicas++;
                // segura que ainda cabem palavras na lista
                if(num_palavras_unicas > num_max_palavras){
                    arq_new_doc.close();
                    cout << "Limite de palavras únicas excedido!" << filename << endl;
                    return EXIT_FAILURE;
                }
                palavras_unicas[num_palavras_unicas-1] = word;
            }
            num_total_palavras++;
            encontrou_palavra = 0;
            arq_new_doc >> word;
        }

        num_total_docs++;
        lista_docs = (int*) realloc(lista_docs, num_total_docs*sizeof(int));
        lista_docs[num_total_docs-1] = id_doc;

        arq_new_doc.close();
    }



    // PREENCHE O HASH
    // cria um hashing com o numero de palavras que descobrimos
    Hash indice(num_palavras_unicas);       // cria o indice/hash
    // percorre o corpus novamente adicionando ao hash pares do tipo
    // (id do documento, frequencia do termo no documento) para todos os termos e documentos
    for(const auto & file : filesystem::directory_iterator(new_corpus_path)){
        string filename = filesystem::path(file.path()).filename().string();    // nome do doc tratado
        ifstream arq_new_doc;       // documento tratado
        arq_new_doc.open(new_corpus_path + filename);
        // testa se o arquivo foi aberto
        if(!arq_new_doc.is_open()){
            cout << "Não foi possível abrir o NOVO documento" << filename << endl;
            return EXIT_FAILURE;
        }

        string id_doc_string = filename;
        id_doc_string.erase(id_doc_string.end()-4, id_doc_string.end());
        int id_doc = stoi(id_doc_string);       // id do documento
        int encontrou_palavra = 0;      // flag para sinalizar se encontrar a palavra na lista
        string palavras_unicas_doc[num_palavras_unicas];       // lista de palavras unicas no doccumento
        int frequencias_doc[num_palavras_unicas];       // lista de frequencias de cada palavra no documento
        int num_palavras_unicas_doc = 0;       // numero de palavras unicas no documento
        arq_new_doc >> word;        // leitura da palavra
        // percorre o documento salvando as ocorrencias das palavras
        while(!arq_new_doc.eof()){
            // caso 1: a palavra ja existe na lista
            for(int i=0; i<num_palavras_unicas_doc; i++){
                if(palavras_unicas_doc[i] == word){
                    frequencias_doc[i] += 1;
                    encontrou_palavra = 1;
                    break;
                }
            }
            // caso 2: a palavra nao existe na lista
            if(encontrou_palavra == 0){
                num_palavras_unicas_doc++;
                palavras_unicas_doc[num_palavras_unicas_doc-1] = word;
                frequencias_doc[num_palavras_unicas_doc-1] = 1;
            }
            encontrou_palavra = 0;
            arq_new_doc >> word;
        }
        // adiciona ao hash todos termos desse documento com suas frequencias
        for(int i=0; i<num_palavras_unicas_doc; i++){
            indice.add(palavras_unicas_doc[i], id_doc, frequencias_doc[i]);
        }
        arq_new_doc.close();
    }


    
    // CALCULA A SIMILARIDADE DE CADA DOCUMENTO COM A CONSULTA
    // abrindo o arquivo com a consulta a ser feita
    ifstream arq_consulta;
    arq_consulta.open(argv[2]);
    // testa se o arquivo foi aberto
    if(!arq_consulta.is_open()){
        cout << "Não foi possível abrir o arquivo de consulta " << argv[2] << endl;
        return EXIT_FAILURE;
    }
    string consultas[num_max_palavras_consulta];
    int num_palavras_consulta = 0;
    // salva as palavras da consulta no vetor consultas
    arq_consulta >> word;
    while(!arq_consulta.eof()){
        num_palavras_consulta++;
        // confirma que nao foi excedido o limite de palavras por consulta
        if(num_palavras_consulta > num_max_palavras_consulta){
            cout << "Limite de palavras da consulta excedido!" << endl;
            return EXIT_FAILURE;
        }
        consultas[num_palavras_consulta-1] = word;

        arq_consulta >> word;
    }
    double peso_t_d = 0;        // peso do termo no documento
    double soma = 0;        // variavel auxiliar
    double norma = 0;       // norma do documento
    double similaridades[num_total_docs];       // vetor para as similaridades
    double pesos[num_palavras_unicas];      // vetor para os pesos das palavras do documento
    double soma_pesos_doc = 0;      // soma dos pesos no documento
    // percorre todos os documentos
    for(int i=0; i<num_total_docs; i++){
        // para cada termo
        for(int j=0; j<num_palavras_unicas; j++){
            // calcula o numero total de documentos sobre o numero de documentos que tem o termo, calcula o 
            // logaritmo neperiano desse quociente e multiplica pela frequencia do termo no documento
            if(indice.quantos_docs_tem(palavras_unicas[j]) == 0) peso_t_d = 0;
            else peso_t_d = log(num_total_docs/indice.quantos_docs_tem(palavras_unicas[j])) * indice.freq_termo_doc(palavras_unicas[j], lista_docs[i]);
            // salva na posição desse documento relativa a esse termo esse valor (o peso do termo no documento)
            pesos[j] = peso_t_d;
            // eleva ao quadrado e soma ao somatorio final
            soma += pow((peso_t_d), 2);
        }
        // tira a raiz quadrada do somatorio e temos a norma desse documento
        norma = sqrt(soma);
        soma = 0;
        peso_t_d = 0;
        
        // percorre as palavras da consulta somando o peso delas nesse doc (se a palavra existir no indice)
        for(int k=0; k<num_palavras_consulta; k++){
            for(int j=0; j<num_palavras_unicas; j++){
                if(palavras_unicas[j] == consultas[k]){
                    soma_pesos_doc += pesos[j];     // soma os pesos apenas dos termos consultados
                    break;
                }
            }
        }
        similaridades[i] = (soma_pesos_doc / norma);    // calcula a similaridade desse doc

        norma = 0;
        soma_pesos_doc = 0;
        arq_consulta.close();
    }


    
    // IMPRIME AS DEZ MAIORES SIMILARIDADES (NÃO NULAS)
    // abrindo o arquivo onde será colocado o ranking (saída)
    ofstream arq_ranking;
    arq_ranking.open(argv[4]);
    // testa se o arquivo foi aberto
    if(!arq_ranking.is_open()){
        cout << "Não foi possível abrir o arquivo de ranking " << argv[4] << endl;
        return EXIT_FAILURE;
    }
    double maior;          // maior similaridade
    int ind_maior;          // indice do documento de maior similaridade
    for(int x=0; x<10; x++){
        maior = similaridades[0];
        ind_maior = 0;
        // percorre as similaridades e imprime a id do doc de maior similaridade não nula
        for(int i=1; i<num_total_docs; i++){
            if(similaridades[i] > maior){     // se esse termo do vetor de similaridades for maior atualizo o maior
                maior = similaridades[i];
                ind_maior = i;
            }
            else if(similaridades[i] == maior){       // se esse termo do vetor de similaridades for igual ao atual maior
                if(lista_docs[i] < lista_docs[ind_maior]){    // o maior sera o de menor id
                    maior = similaridades[i];
                    ind_maior = i;
                }
            }
        }
        // aqui o maior já foi encontrado
        // imprimo esse maior se ele for diferente de zero
        if(similaridades[ind_maior] != 0.0){
            arq_ranking << lista_docs[ind_maior] << " ";
        }
        // se ele for igual a zero eu finalizo as impressoes pois as similaridades nao nulas acabaram
        else break;
        similaridades[ind_maior] = 0;       // zera a similaridade que ja foi impressa para ela nao ser impressa novamente
    }
    arq_ranking.close();

    free(lista_docs);
    return 0;
}