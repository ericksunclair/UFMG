#include<iostream> 
#include "Ponto2D.h"

Ponto2D& Ponto2D::operator-- (void){
    x -= 1;
    y -= 1;
    return *this;
}

Ponto2D Ponto2D::operator+ (const Ponto2D& p2) const{
    class Ponto2D p3;
    p3.setX(x + p2.getX());
    p3.setY(y + p2.getY());
    return p3;
}