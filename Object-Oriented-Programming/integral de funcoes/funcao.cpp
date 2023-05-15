#include "funcao.h"
#include <iostream>
#include <cmath>
using namespace std;

double Funcao::getIntegral(double limiteInferior, double limiteSuperior, double intervalos){
    double espaco = (limiteSuperior - limiteInferior) / intervalos;
    double area = 0; 
    for(int i=0, j=0; j<intervalos; i+=espaco, j++){
        if(func(limiteInferior + i + espaco) > func(limiteInferior + i)){
            area += espaco * func(limiteInferior + i);
            area += espaco * (func(limiteInferior + i + espaco) - func(limiteInferior + i)) / 2;
        }
        else if (func(limiteInferior + i + espaco) < func(limiteInferior + i)){
            area += espaco * func(limiteInferior + i + espaco);
            area += espaco * (func(limiteInferior + i) - func(limiteInferior + i + espaco)) / 2;
        }
        else{
            area += espaco * func(limiteInferior + i);
        }

    }
    return area;
}