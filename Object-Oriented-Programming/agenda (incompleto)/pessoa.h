#ifndef PESSOA_H
#define PESSOA_H

#include <string>
using namespace std;

class pessoa{
    protected:
    string nome;
    int idade;

    public:
    pessoa(){ nome = "indefinido"; idade = 0; }
    pessoa(string _nome, int _idade): nome(_nome), idade(_idade) { };
    virtual ~pessoa();
    string get_nome() const{ return nome; };
    int get_idade() const{ return idade; };
    void set_nome(const string &_nome){ nome = _nome; }
    void set_idade(const int &_idade){ idade = _idade; }
    virtual int tipo_pessoa() const{ return 0; };
};

#endif