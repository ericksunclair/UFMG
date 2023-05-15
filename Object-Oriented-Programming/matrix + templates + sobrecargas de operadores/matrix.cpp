// matrix.cpp
#include "matrix.h"
#include <iostream>
#include <fstream> 
#include <ostream>
using namespace std;

// contrutor default - cria uma matriz vazia com nRows = nCols = 1 
template <class TValor>
Matrix<TValor>::Matrix(){
    nRows = 1;
    nCols = 1;
    
    m = (TValor**) malloc(sizeof(TValor*)*nRows);   // aloca as linhas da matriz
    for (int i=0; i<nRows; i++){
        m[i] = (TValor*) malloc(sizeof(TValor)*nCols);  // aloca as colunas pra cada linha da matriz
    }
}

// contrutor parametrico 1 - cria uma matriz com nRows  = rows, nCols = cols e 
// com todos os elementos iguais a 0
template <class TValor>
Matrix<TValor>::Matrix(int rows, int cols){
    nRows = rows;
    nCols = cols;
    
    m = (TValor**) malloc(sizeof(TValor*)*nRows);   // aloca as linhas da matriz
    for (int i=0; i<nRows; i++){
        m[i] = (TValor*) malloc(sizeof(TValor)*nCols);  // aloca as colunas pra cada linha da matriz
    }

    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            m[i][j] = 0;
        }
    }
}


// contrutor parametrico 2 - cria uma matriz com nRows  = rows, nCols = cols e 
// com todos os elementos iguais a elem (do tipo TValor)
template <class TValor>
Matrix<TValor>::Matrix(int rows, int cols, const TValor& value){
    nRows = rows;
    nCols = cols;
    
    m = (TValor**) malloc(sizeof(TValor*)*nRows);   // aloca as linhas da matriz
    for (int i=0; i<nRows; i++){
        m[i] = (TValor*) malloc(sizeof(TValor)*nCols);  // aloca as colunas pra cada linha da matriz
    }

    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            m[i][j] = value;
        }
    }
}

// construtor por cópia
template <class TValor>
Matrix<TValor>::Matrix(const Matrix& that){
    nRows = that.nRows;
    nCols = that.nCols;
    
    m = (TValor**) malloc(sizeof(TValor*)*nRows);   // aloca as linhas da matriz
    for (int i=0; i<nRows; i++){
        m[i] = (TValor*) malloc(sizeof(TValor)*nCols);  // aloca as colunas pra cada linha da matriz
    }

    for(int i=0; i<nRows; i++){
        for(int j=0; j<nCols; j++){
            m[i][j] = that.get(0, 0);
        }
    }
}


// destrutor
template <class TValor>
Matrix<TValor>::~Matrix() {
    for(int i=0; i<nRows; i++){
        delete m[i];
    }
    delete m;
}


// obtem o numero de linhas
template <class TValor>
int Matrix<TValor>::getRows() const {
    return nRows;
}

// obtem o numero de colunas
template <class TValor>
int Matrix<TValor>::getCols() const {
    return nCols;
}

// retorna uma matriz transposta
template <class TValor>
Matrix<TValor> Matrix<TValor>::transpose() {
    TValor **t = (TValor**) malloc(sizeof(TValor*)*nCols);   // aloca as linhas da matriz
    for (int i=0; i<nRows; i++){
        t[i] = (TValor*) malloc(sizeof(TValor)*nRows);  // aloca as colunas pra cada linha da matriz
    }

    for(int i=0; i<nRows; i++){
        for(int j=0; j<nCols; j++){
            t[j][i] = m[i][j];
        }
    }
    Matrix mt(nCols, nRows, t[0][0]);
    return mt;
}

// imprime o conteudo da matriz
template <class TValor>
void Matrix<TValor>::print() const {
    for(int i=0; i<nRows; i++){
        for(int j=0; j<nCols; j++){
            std::cout <<  m[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// faz com que a matriz torne-se uma matriz identidade
template <class TValor>
void Matrix<TValor>::unit(){
    for(int i=0; i<nRows; i++){
        for(int j=0; j<nCols; j++){
            if(i==j)
                m[i][j] = 1;
            else
                m[i][j] = 0;
        }
    }
}

// faz com que a matriz torne-se uma matriz nula
template <class TValor>
void Matrix<TValor>::zeros(){
    for(int i=0; i<nRows; i++){
        for(int j=0; j<nCols; j++){
            m[i][j] = 0;
        }
    }
}

// faz com que a matriz torne-se uma matriz cujos elementos sao iguais a 1
template <class TValor>
void Matrix<TValor>::ones(){
    for(int i=0; i<nRows; i++){
        for(int j=0; j<nCols; j++){
            m[i][j] = 1;
        }
    }
}

// operador de deslocamento <<
template <class TValor>
ostream& operator<<(ostream &op, const Matrix<TValor> &matriz){
    op << endl;
    for(int i=0; i<matriz.getRows(); i++){
        for(int j=0; j<matriz.getCols(); j++){
            op << matriz.get(i, j) << " ";
        }
        op << endl;
    }
    op << endl;
    return op;
}

// retorna um ponteiro para a o termo da matriz Matrix[row][col]
template <class TValor>
TValor& Matrix<TValor>::operator()(const int row, const int col) const{
    return m[row-1][col-1];
}

// obtem um elemento específico na posição (row,col).
template <class TValor>
TValor& Matrix<TValor>::get(const int row, const int col) const {
    return m[row][col];
}