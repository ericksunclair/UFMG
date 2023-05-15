#include <iostream>
#include "ponto3D.h"
#include "box.h"
using namespace std;

int main(){
    Ponto3D p1(0, 0, 2);
    Ponto3D p2(2, 0, 2);
    Ponto3D p3(2, 2, 2);
    Ponto3D p4(0, 2, 2);
    Ponto3D p5(0, 0, 0);
    Ponto3D p6(2, 0, 0);
    Ponto3D p7(2, 2, 0);
    Ponto3D p8(0, 2, 0);

    box b(p1, p2, p3, p4, p5, p6, p7, p8);
    cout << "largura: " << b.get_largura() << "\naltura: " << b.get_altura() << "\nprofundidade: " << b.get_profundidade() << endl;
    cout << "area: " << b.area() << "\nvolume: " << b.volume();

    return 0;
}