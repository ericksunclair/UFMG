#ifndef QUADRATICA_H
#define QUADRATICA_H

#include "funcao.h"
#include <iostream>
#include <cmath>
using namespace std;

class Quadratica: public Funcao{
    private:
        double a, b, c;

    public:
        Quadratica(double _a, double _b, double _c): a(_a), b(_b), c(_c) {};
        double func(double input){ return a*pow(input, 2) + b*input + c; };
        ~Quadratica(){};
};

#endif