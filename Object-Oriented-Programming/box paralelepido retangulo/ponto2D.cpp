// ponto2D.cpp
#include <iostream>
#include "ponto2D.h"
using namespace std;

Ponto2D& Ponto2D::operator= (const Ponto2D &p){
    x = p.get_x();
    y = p.get_y();
    return *this;
}

ostream& operator<< (ostream &op, const Ponto2D &p){
            op << endl;
            op << "x = " << p.get_x() << endl;
            op << "y = " << p.get_y() << endl;
            return op;
}