// ponto3D.cpp
#include <iostream>
#include "ponto3D.h"
#include "math.h"
using namespace std;

Ponto3D& Ponto3D::operator= (const Ponto2D &p){
    x = p.get_x();
    y = p.get_y();
    z = 0;
    return *this;
}

ostream& operator<< (ostream &op, const Ponto3D &p){
            op << endl;
            op << "x = " << p.get_x() << endl;
            op << "y = " << p.get_y() << endl;
            op << "z = " << p.get_z() << endl;
            return op;
}

double Ponto3D::distancia (const Ponto3D &p2) const{
    return sqrt( pow(x-p2.get_x(), 2) + pow(y-p2.get_y(), 2) + pow(z-p2.get_z(), 2) );
}