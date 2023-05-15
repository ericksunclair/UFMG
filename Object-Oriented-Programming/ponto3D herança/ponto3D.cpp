// ponto3D.cpp
#include <iostream>
#include "ponto3D.h"
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