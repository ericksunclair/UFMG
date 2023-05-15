// ponto2D.h (header file)
#ifndef PONTO2D_H
#define PONTO2D_H

#include<iostream> 
using namespace std;

class Ponto2D{
    protected:
        double x;
        double y;

     public:
        Ponto2D(double xx = 0.0, double yy = 0.0):x(xx),y(yy){ };
        friend ostream& operator<< (ostream &op, const Ponto2D &p);
        Ponto2D& operator= (const Ponto2D &p);
        ~Ponto2D(){};
        double get_x(void) const { return x; }
        double get_y(void) const { return y; }
        void set (double nx, double ny) { x=nx; y=ny; }
};

#endif