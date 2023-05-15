#ifndef LINEAR_H
#define LINEAR_H

#include "funcao.h"
#include <iostream>
#include <cmath>
using namespace std;

class Linear: public Funcao{
    private:
        double a, b;

    public:
        Linear(double _a, double _b): a(_a), b(_b) {};
        double func(double input){ return a*input + b; };
        ~Linear(){};
};

#endif