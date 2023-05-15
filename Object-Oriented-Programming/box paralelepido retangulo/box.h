#ifndef BOX_H
#define BOX_H

#include "paralelogramo.h"
using namespace std;

class box{
    protected:
    paralelogramo f1;
    paralelogramo f2;
    paralelogramo f3;
    paralelogramo f4;
    paralelogramo f5;
    paralelogramo f6;
    double largura;
    double altura;
    double profundidade;

    public:
    box(const Ponto3D &_p1, const Ponto3D &_p2, const Ponto3D &_p3, const Ponto3D &_p4, const Ponto3D &_p5, const Ponto3D &_p6, const Ponto3D &_p7, const Ponto3D &_p8);
    double area() const;
    double volume() const;
    double get_altura() { return altura; }
    double get_largura() { return largura; }
    double get_profundidade() { return profundidade; }
};

#endif