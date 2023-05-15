// ponto3D.h (header file)
#ifndef PONTO3D_H
#define PONTO3D_H

#include <iostream>
#include "ponto2D.h"
using namespace std;

class Ponto3D : public Ponto2D{
    protected:
        double z;

    public:
        Ponto3D(double xx = 0.0, double yy = 0.0, double zz=0.0) : Ponto2D(xx, yy), z(zz){ };
        friend ostream& operator<< (ostream &op, const Ponto3D &p);
        Ponto3D& operator= (const Ponto2D &p);
        void set(double nx = 0, double ny = 0, double nz=0){ x=nx; y=ny; z=nz; };
        double get_z(void) const { return z; }
        double distancia(const Ponto3D &p2) const;
};

#endif