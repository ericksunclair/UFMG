// matrix.cpp
#include "matrix.h"

// contrutor default - cria uma matriz vazia com nRows = nCols = 0  
Matrix::Matrix(){
    nRows = 0;
    nCols = 0;
    
    m = (double**) malloc(sizeof(double*)*nRows);   // aloca as linhas da matriz
    for (int i=0; i<nRows; i++){
        m[i] = (double*) malloc(sizeof(double)*nCols);  // aloca as colunas pra cada linha da matriz
    }
}
    

// contrutor parametrico 1 - cria uma matriz com nRows  = rows, nCols = cols e 
// com todos os elementos iguais a elem (double)
Matrix::Matrix(int rows, int cols, double elem){
    nRows = rows;
    nCols = cols;
    
    m = (double**) malloc(sizeof(double*)*nRows);   // aloca as linhas da matriz
    for (int i=0; i<nRows; i++){
        m[i] = (double*) malloc(sizeof(double)*nCols);  // aloca as colunas pra cada linha da matriz
    }

    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            m[i][j] = elem;
        }
    }
}


// destrutor
Matrix::~Matrix() {
    for(int i=0; i<nRows; i++){
        delete m[i];
    }
    delete m;
}


// obtem o numero de linhas
int Matrix::getRows() const {
    return nRows;
}

// obtem o numero de colunas
int Matrix::getCols() const {
    return nCols;
}

// retorna uma matriz transposta
Matrix Matrix::transpose() {
    double **t = (double**) malloc(sizeof(double*)*nCols);   // aloca as linhas da matriz
    for (int i=0; i<nRows; i++){
        t[i] = (double*) malloc(sizeof(double)*nRows);  // aloca as colunas pra cada linha da matriz
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
void Matrix::print() const {
    for(int i=0; i<nRows; i++){
        for(int j=0; j<nCols; j++){
            std::cout <<  m[i][j] << " ";
        }
        std::cout << std::endl;
    }
}