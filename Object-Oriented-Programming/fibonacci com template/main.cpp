#include <stdio.h>
#include <iostream>
using namespace std;

template<typename T>
T fibonacci(const int &termo){
    if(termo == 1)   return 0;
    else if(termo == 2)  return 1;
    else{
        return (T) fibonacci<T>(termo-1) + fibonacci<T>(termo-2);
    }
}


int main(){
    cout << "Fibonacci termo 1: " << fibonacci<int>(1) << endl;
    cout << "Fibonacci termo 2: " << fibonacci<long unsigned int>(2) << endl;
    cout << "Fibonacci termo 3: " << fibonacci<long>(3) << endl;
    cout << "Fibonacci termo 4: " << fibonacci<float>(4) << endl;
    cout << "Fibonacci termo 10: " << fibonacci<int>(10) << endl;
    cout << "Fibonacci termo 11: " << fibonacci<float>(11) << endl;


    return 0;
}