#ifndef SENOIDE_H
#define SENOIDE_H

#include "funcao.h"
#include <iostream>
#include <cmath>
using namespace std;

class Senoide: public Funcao{
    private:

    public:
        Senoide(){};
        double func(double input){ return sin(input) / input; };
        ~Senoide(){};
};

#endif