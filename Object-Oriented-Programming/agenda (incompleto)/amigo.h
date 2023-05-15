#ifndef AMIGO_H
#define AMIGO_H

#include "pessoa.h"
#include <string>
using namespace std;

class amigo : public pessoa{
    protected:
    string aniversario;

    public:
    amigo(): pessoa::pessoa(), aniversario("indefinido") { };
    virtual ~amigo();
    string get_aniversario() const{ return aniversario; }
    void set_aniversario(const string &_aniversario){ aniversario = _aniversario; }
    int tipo_pessoa() const{ return 1; }
};

#endif