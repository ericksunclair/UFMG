#ifndef AGENDA_H
#define AGENDA_H

#include "pessoa.h"
#include "amigo.h"
#include "conhecido.h"
#include <string>
#include <vector>
using namespace std;

class agenda{
    protected:
    vector<pessoa *> todos;
    int qt_amigos;
    int qt_conhecidos;

    public:
    agenda(int num_pessoas);
    int get_qt_amigos() const{ return qt_amigos; }
    int get_qt_conhecidos() const{ return qt_conhecidos; }
    void add_informacoes();
    void imprime_aniversarios() const;
    void imprime_emails() const;
};

#endif