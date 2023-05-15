#ifndef CONHECIDO_H
#define CONHECIDO_H

#include "pessoa.h"
#include <string>
using namespace std;

class conhecido : public pessoa{
    protected:
    string email;

    public:
    conhecido(): pessoa::pessoa(), email("indefinido") { };
    virtual ~conhecido();
    string get_email() const{ return email; }
    void set_email(const string &_email){ email = _email; }
    int tipo_pessoa() const{ return 2; }
};

#endif