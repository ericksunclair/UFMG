#include <string>
#include <vector>
#include "universidade.h"

double Universidade::totalPago() const{
    double soma = 0;
        for(int i=0; i<(int)professores.size(); i++) soma +=professores[i]->getSalario();
    return soma;
}