// main.cpp
#include "ponto2D.h"
using namespace std;

int main()
{
    class ponto2D p1;
    class ponto2D p2(4.3, 7.6);
    class ponto2D p3;
    cout << "p1:: " << endl << "x: " << p1.getX() << " , y: " << p1.getY() << " , id: " << p1.getId() << endl;
    cout << "p2:: " << endl << "x: " << p2.getX() << " , y: " << p2.getY() << " , id: " << p2.getId() << endl;
    cout << "p3:: " << endl << "x: " << p3.getX() << " , y: " << p3.getY() << " , id: " << p3.getId() << endl;
    
    cout << "p1 (usando print()):: " << endl;
    p1.print();
    p1.sumOf(p2);
    cout << "p1 após somar com p2:: " << endl;
    p1.print();

    class ponto2D p4;
    p4 = p1.sumOf2(p2);
    cout << "p4 (soma de p1 e p2):: " << endl;
    p4.print();
    cout << "distância de p4 pra origem: " << p4.distToOrig() << endl;
    cout << "distância de p4 pra p2: " << p4.distTo(p2) << endl;

    return 0;
}