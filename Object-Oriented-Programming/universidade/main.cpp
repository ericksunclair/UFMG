#include "professor.h"
#include "profIntegral.h"
#include "profHorista.h"
#include "universidade.h"
#include <iostream>
using namespace std;

int main(){
    ProfHorista p1("Lucas", 6, 197.54);
    ProfHorista p2("Marcos", 5, 300);
    ProfIntegral p3("Pedro", 10000);
    Universidade UFMG;
    UFMG.addProfessor(&p1);
    UFMG.addProfessor(&p2);
    UFMG.addProfessor(&p3);

    cout << "Professor 1: " << p1.getName() << ", salário: " << p1.getSalario() << endl;
    cout << "Professor 2: " << p2.getName() << ", salário: " << p2.getSalario() << endl;
    cout << "Professor 3: " << p3.getName() << ", salário: " << p3.getSalario() << endl;

    cout << "Valor total mensal pago pela universidade aos professores: " << UFMG.totalPago() << endl;
    return 0;
}