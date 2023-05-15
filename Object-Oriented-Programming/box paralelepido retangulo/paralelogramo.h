#ifndef PARALELOGRAMO_H
#define PARALELOGRAMO_H

#include "ponto3D.h"

class paralelogramo{
    protected:
    Ponto3D p1;
    Ponto3D p2;
    Ponto3D p3;
    Ponto3D p4;

    public:
    paralelogramo();
    paralelogramo(const Ponto3D &_p1, const Ponto3D &_p2, const Ponto3D &_p3, const Ponto3D &_p4) : p1(_p1), p2(_p2), p3(_p3), p4(_p4) { };
    void set(const Ponto3D _p1, const Ponto3D _p2, const Ponto3D _p3, const Ponto3D _p4) { p1=_p1; p2=_p2; p3=_p3; p4=_p4; }
    double lado1(void) const;
    double lado2(void) const;
    double area(void) const;
};

#endif