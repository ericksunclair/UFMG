// matrix.h (header file)

#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>
#include <fstream>
#include <ostream>
using namespace std;

template <class TValor>
class Matrix {
    private:

        TValor** m; // m é um array 2D a ser implementado como um pointer de pointers
        int nRows;  // numero de linhas
        int nCols;  //  numero de colunas

    public:

        //Construtores
        Matrix();
        Matrix(int rows, int cols);
        Matrix(int rows, int cols, const TValor& value);
        Matrix(const Matrix &that);

        // Destrutor
        ~Matrix();

        TValor& operator()(const int row, const int col) const;

        // basic getters
        int getRows() const;
        int getCols() const;
        TValor& get(int row, int col) const;   
        
        // other methods
        Matrix transpose();  
        void print() const;
        void unit();
        void zeros();
        void ones();      
        
};

template <class TValor>
ostream& operator<<(ostream &op, const Matrix<TValor> &matriz);

#endif