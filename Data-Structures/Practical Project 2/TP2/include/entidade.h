//---------------------------------------------------------------------
// Arquivo	: entidade.h
// Conteudo	: definições do tipo entidade
// Autor	: Erick Sunclair (ericksunclair@ufmg.br)
// Data     : 12/01/2021
//---------------------------------------------------------------------

#ifndef ENTIDADE
#define ENTIDADE

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// tipo que vai representar cada entidade
class entidade{
    private:
        string url;             // url
        int num_acessos;        // numero de acessos dessa url
        int ind_rodada;         // indice que indica a rodada de onde veio essa entidade

    public:
        // construtor da classe entidade
        entidade(){ url = ""; num_acessos = -1; ind_rodada = -1; }

        // outros métodos
        // setter para o atributo url
        void set_url(const string &_url){ url = _url; }
        // setter para o atributo num_acessos
        void set_num_acessos(const int &_num_acessos){ num_acessos = _num_acessos; }
        // setter para o atributo ind_rodada
        void set_ind_rodada(const int &_ind_rodada){ ind_rodada = _ind_rodada; }
        // getter para o atributo url
        string get_url() const{ return url; };
        // getter para o atributo num_acessos
        int get_num_acessos() const{ return num_acessos; };
        // getter para o atributo ind_rodada
        int get_ind_rodada() const{ return ind_rodada; };
        // sobrecarga do operador de atribuição
        entidade& operator= (const entidade &ent){ url = ent.get_url();
            num_acessos = ent.get_num_acessos(); ind_rodada = ent.get_ind_rodada(); return *this; };

    friend class fita;
};


#endif