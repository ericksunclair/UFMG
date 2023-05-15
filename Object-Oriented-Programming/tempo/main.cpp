// main.cpp
#include "tempo.h"

int main()
{
    class tempo tp1;
    class tempo tp2(1);
    class tempo tp3(45, 30, 37);
    class tempo tp4(3, 40, 20, 30);
    std::cout << "tp1::" << std::endl;
    tp1.print();
    std::cout << "tp2::" << std::endl;
    tp2.print();
    std::cout << "tp3::" << std::endl;
    tp3.print();
    std::cout << "tp4::" << std::endl;
    tp4.print();

    tp3.dec();
    std::cout << "tp3 decrementado::" << std::endl;
    tp3.print();


   
    return 0;
}