#ifndef PROFHORISTA
#define PROFHORISTA

#include <string>
#include "professor.h"
using namespace std;

class ProfHorista: public Professor {
        double nrNorasTrabalhadas;
        double valorHora;
    public:
        ProfHorista(string n, double nht, double vh): Professor(n), nrNorasTrabalhadas(nht), valorHora(vh){};
        double getSalario() const{ return nrNorasTrabalhadas * valorHora; }
};

#endif