#include <iostream>

#include "agenda.h"
using namespace std;

int main(){
    cout << "Diga a quantidade de pessoas: " << endl;
    int p;
    agenda(p);
    cout << "Amigos: " << agenda.get_qt_amigos() << endl;
    cout << "Conhecidos: " << agenda.get_qt_conhecidos() << endl;

    return 0;
}