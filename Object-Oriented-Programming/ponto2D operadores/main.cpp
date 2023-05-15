#include<iostream> 
#include "Ponto2D.h"
using namespace std;

int main() {
    class Ponto2D a(1,4), b(3,2), c;
    c = a + b;               // soma as coordenadas dos pontos a e b 
    cout << "c.x: " << c.getX() << " c.y: " << c.getY() << endl;
    --c;                    // decrementa em uma unidade as coordenadas de c
    cout << "c.x: " << c.getX() << " c.y: " << c.getY() << endl;

    return 0;
}