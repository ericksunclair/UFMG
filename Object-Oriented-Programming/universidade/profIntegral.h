#ifndef PROFINTEGRAL
#define PROFINTEGRAL

#include <string>
#include "professor.h"
using namespace std;

class ProfIntegral: public Professor {
        double salarioMensal;
    public:
       ProfIntegral(string n, double sm): Professor(n), salarioMensal(sm){};
       double getSalario() const{ return salarioMensal; }
};

#endif