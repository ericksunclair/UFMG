// ponto2D.h (header file)

#include <iostream>
#include <vector>
using namespace std;

class ponto2D {
    private:
        double x;
        double y;
        unsigned int id;
        unsigned int getNextId(int i);

    public:
        // contrutores
        ponto2D(): x(.0), y(.0), id(getNextId(1)){};
        ponto2D(double _x, double _y): x(_x), y(_y), id(getNextId(1)){};
        // destrutor
        ~ponto2D() {
            getNextId(0);
        }
        
        // // getters and setters
        double getX(void) const{  return x;   }
        double getY(void) const{   return y;   }
        double getId(void) const{   return id;   }

        // // outras funções
        // Função membro para escrever (imprimir) as coordenadas do ponto na tela
        void print() const;
        // Função membro para calcular a distância do ponto a origem do sistema de coordenadas cartesiano
        double distToOrig() const;
        // Função membro para calcular a distância entre dois pontos p1 e p2, onde p1 é o objeto que chama a função
        double distTo(const class ponto2D &p2) const;
        // Função membro que modifica as coordenadas do objeto corrente p1 somando às 
        // suas coordenadas um novo ponto p2, que deve ser passado por argumento. 
        void sumOf(const class ponto2D &p2);
        // Função membro que retorna um ponto p3 que é o resultado da soma entre dois pontos p1 e p2, 
        // onde p1 é o objeto que chama a função. 
        class ponto2D sumOf2(const class ponto2D &p2) const;
};