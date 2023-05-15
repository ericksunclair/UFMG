#ifndef UNIVERSIDADE
#define UNIVERSIDADE

#include <string>
#include <vector>
#include "professor.h"
using namespace std;

class Universidade{
        vector<Professor *> professores;
    public:
        Universidade(){};
        void addProfessor(Professor *prof){ professores.push_back(prof); }
        double totalPago() const;
};

#endif