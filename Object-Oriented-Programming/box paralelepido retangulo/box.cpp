#include "box.h"
using namespace std;

box::box(const Ponto3D &_p1, const Ponto3D &_p2, const Ponto3D &_p3, const Ponto3D &_p4, const Ponto3D &_p5, const Ponto3D &_p6, const Ponto3D &_p7, const Ponto3D &_p8){
    // inicializando cada uma das 6 faces do paralelepído
    f1.set(_p1, _p2, _p3, _p4);     // manter sempre a mesma ordem de vértices
    f2.set(_p5, _p6, _p7, _p8);     // para não alterar os calculos de medidas
    f3.set(_p1, _p5, _p8, _p4);
    f4.set(_p2, _p6, _p7, _p3);
    f5.set(_p1, _p2, _p6, _p5);
    f6.set(_p4, _p3, _p7, _p8);
    // inicializar os parâmetros altura, largura e profundidade
    largura = f1.lado1();
    altura = f1.lado2();
    profundidade = f3.lado1();
}

double box::area() const{
    return f1.area() + f2.area() + f3.area() + f4.area() + f5.area() + f6.area();
}


double box::volume() const{
    return largura * altura * profundidade;
}