#ifndef PROFESSOR
#define PROFESSOR

#include <string>
using namespace std;

class Professor{
        string nome;
    public:
        Professor(string n){ nome = n; }
        string getName() const { return nome; }
        virtual double getSalario() const = 0;
};

#endif