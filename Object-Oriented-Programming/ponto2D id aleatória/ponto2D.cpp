// ponto2D.cpp
#include "ponto2D.h"
#include <math.h>
using namespace std;

// retorna o próximo id disponível
unsigned int ponto2D::getNextId(int i){
    static vector<unsigned int> id_geral;
    if(i==1){               // i==1 --> construtor
        if(id_geral.size()==0){
            unsigned seed = time(0);
            srand(seed);
            id_geral.push_back(rand()%1000);
            return id_geral.back();
        }
        else{
            while(1){
                int c = 0;
                unsigned seed = time(0);
                srand(seed);
                unsigned int val = rand()%1000;
                for(unsigned int i=0; i<id_geral.size(); i++){
                    if((val)==id_geral[i])
                        c=1;
                }
                if(c==0){
                    id_geral.push_back(val);
                    return id_geral.back();
                }
            }
        }
    }
    if(i==0){               // i==0 --> destrutor
        id_geral.pop_back();
    }
    return id_geral.back();
}

// // getters and setters
// Função membro para escrever (imprimir) as coordenadas do ponto na tela
void ponto2D::print() const{
    cout << "x: " << x << " , y: " << y << endl;
}

// Função membro para calcular a distância do ponto a origem do sistema de coordenadas cartesiano
double ponto2D::distToOrig() const{
    return sqrt(pow(x, 2) + pow(y, 2));
}

// Função membro para calcular a distância entre dois pontos p1 e p2, onde p1 é o objeto que chama a função
double ponto2D::distTo(const class ponto2D &p2) const{
    return sqrt(pow(x-p2.getX(), 2) + pow(y-p2.getY(), 2));
}

// Função membro que modifica as coordenadas do objeto corrente p1 somando às 
// suas coordenadas um novo ponto p2, que deve ser passado por argumento. 
void ponto2D::sumOf(const class ponto2D &p2){
    x += p2.getX();
    y += p2.getY();
}

// Função membro que retorna um ponto p3 que é o resultado da soma entre dois pontos p1 e p2, 
// onde p1 é o objeto que chama a função. 
class ponto2D ponto2D::sumOf2(const class ponto2D &p2) const{
    class ponto2D p3(x+p2.getX(), y+p2.getY());
    return p3;
}