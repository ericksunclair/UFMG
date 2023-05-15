//---------------------------------------------------------------------
// Arquivo	: main.cpp
// Conteudo	: programa de operação do algoritmo de ordenação
// Autor	: Erick Sunclair (ericksunclair@ufmg.br)
// Data     : 12/01/2021
//---------------------------------------------------------------------

#include <string>
#include <iostream>
#include <fstream>
#include "fita.h"
#include "entidade.h"
#include "heap.h"

using namespace std;

int main(int argc, char * argv[]){
    // abrindo o arquivo de entrada
    ifstream arq_in;
    arq_in.open(argv[1]);
    
    // abrindo o arquivo de saída
    ofstream arq_out;
    arq_out.open(argv[2]);

    // salva os outros parâmetros
    int num_entidades_rodada = stoi(argv[3]);
    int num_fitas = 0;

    // variavel que vai armazenar qual a rodada atual
    int rodada_atual = 1;
    // variavel para pegar palavras dos arquivos
    string palavra;

    // testa se os arquivos foram abertos
    if(!arq_in.is_open()){
        cout << "Não foi possível abrir o arquivo de entrada" << endl;
        return EXIT_FAILURE;
    }
    else if(!arq_out.is_open()){
        cout << "Não foi possível abrir o arquivo de saída" << endl;
        return EXIT_FAILURE;
    }
    // realiza os comandos descritos no arquivo
    else{
        // Primeira Etapa: criação das rodadas/fitas
        // para cada fita
        // for(int i=0; i<num_fitas; i++){
        while(!arq_in.eof()){
            // incializa uma instancia da classe fita
            fita Fita(num_entidades_rodada);
            // salva na fita atual o numero de entidades desejadas do arq_in
            Fita.le_entidades(arq_in);
            // ordena as entidades (usando quicksort) - maior num de acessos primeiro
            Fita.ordena_entidades();
            // escreve as entidades ordenadas no arquivo de saída
            Fita.escreve_entidades("rodadas/rodada-"+to_string(rodada_atual)+".txt");
            // atualiza o indice da rodada
            rodada_atual++;
            num_fitas++;
        }

        // Segunda Etapa: intercala as fitas
        // incializa uma classe heap
        heap Heap(num_fitas);
        // cria um vetor de streams de entrada para armazenar os arquivos das rodadas
        ifstream fitas[num_fitas];
        // adiciona ao heap a primeira entidade de cada arquivo de rodada
        for(int i=0; i<num_fitas; i++){
            // abre o arquivo
            fitas[i].open("rodadas/rodada-"+to_string(i+1)+".txt");
            // testa se os arquivos foram abertos
            if(!fitas[i].is_open()){
                cout << "Não foi possível abrir a fita" << endl;
                return EXIT_FAILURE;
            }
            // inicializa uma entidade temporaria
            entidade *Entidade = new entidade;
            // pega a primeira url dessa rodada e salva na entidade
            fitas[i] >> palavra;
            Entidade->set_url(palavra);
            // pega o primeiro numero de acessos dessa rodada e salva na entidade
            fitas[i] >> palavra;
            Entidade->set_num_acessos(stoi(palavra));
            // define o indice da rodada dessa entidade
            Entidade->set_ind_rodada(i+1);
            // adiciona ao heap (já na posição correta) a entidade
            Heap.adiciona(*Entidade);
            // apaga a entidade temporaria
            delete Entidade;
        }
        // ordena o heap
        Heap.ordena_entidades();
        // enquanto o heap nao estiver vazio
        while(Heap.get_tamanho()){
            // inicializa uma entidade temporaria
            entidade *Entidade = new entidade;
            // retiro a primeira entidade do heap (a de maior num de acessos)
            *Entidade = Heap.retira();
            // escrevo no arquivo de saida essa entidade
            arq_out << Entidade->get_url() << " " << to_string(Entidade->get_num_acessos()) << endl;
            // pego o indice da rodada da entidade que eu acabei de imprimir
            int rodada = Entidade->get_ind_rodada();
            // apaga a entidade temporaria
            delete Entidade;
            // se o documento não estiver vazio
            if(!fitas[rodada-1].eof()){
                // inicializa uma entidade temporaria
                entidade *Entidade = new entidade;
                // pega a proxima url dessa rodada e salva na entidade
                fitas[rodada-1] >> palavra;
                Entidade->set_url(palavra);
                // pega o primeiro numero de acessos dessa rodada e salva na entidade
                fitas[rodada-1] >> palavra;
                Entidade->set_num_acessos(stoi(palavra));
                // define o indice da rodada dessa entidade
                Entidade->set_ind_rodada(rodada);
                // adiciona ao heap (já na posição correta) a entidade
                Heap.adiciona(*Entidade);
                // apaga a entidade temporaria
                delete Entidade;
                // ordena o heap
                Heap.ordena_entidades();
            }
        }
    }

    // fecha os arquivos
    arq_in.close();
    arq_out.close();
    return 0;
}