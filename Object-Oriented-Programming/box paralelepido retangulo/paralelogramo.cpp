#include "math.h"
#include "paralelogramo.h"
using namespace std;

paralelogramo:: paralelogramo(){
    Ponto3D x;
    p1 = x;
    p2 = x;
    p3 = x;
    p4 = x;
}

double paralelogramo::lado1() const{
    return sqrt(pow(p2.get_x()-p1.get_x(), 2) + pow(p2.get_y()-p1.get_y(), 2) + pow(p2.get_z()-p1.get_z(), 2));
}

double paralelogramo::lado2() const{
    return sqrt(pow(p3.get_x()-p2.get_x(), 2) + pow(p3.get_y()-p2.get_y(), 2) + pow(p3.get_z()-p2.get_z(), 2));
}

double paralelogramo::area() const{
    return lado1() * lado2();
}