// main.cpp

#include "matrix.h"
#include <iostream>
#include <fstream>

int main()
{
    std::ifstream in("myMatrix.txt");
    Matrix Y;
    Matrix X(3,1);
    Matrix Z(3,2,7.0);
    Matrix W(in);
    
    std::cout << "X:: " << std::endl;
    X.print();
    std::cout << "Numero de linhas de X:: " << X.getRows() << std::endl;
    std::cout << "Numero de colunas de X:: " << X.getCols() << std::endl;
    std::cout << "Primeiro elemento de X:: " << X.get(0, 0) << std::endl;
   
    std::cout << "J é transposta de X:: " << std::endl;
    Matrix J = X.transpose();
    J.print();
    std::cout << "Numero de linhas de J:: " << J.getRows() << std::endl;
    std::cout << "Numero de colunas de J:: " << J.getCols() << std::endl;
    std::cout << "Primeiro elemento de J:: " << J.get(0, 0) << std::endl;
    
    std::cout << "Z:: " << std::endl;
    Z.print();
    std::cout << "Z nula:: " << std::endl;
    Z.zeros();
    Z.print();

    std::cout << "Y:: " << std::endl;
    Y.print();
    std::cout << "Y identidade:: " << std::endl;
    Y.unit();
    Y.print();

    std::cout << "W:: " << std::endl;
    W.print();
    std::cout << "W com apenas 'uns':: " << std::endl;
    W.ones();
    W.print();
    
    return 0;
}