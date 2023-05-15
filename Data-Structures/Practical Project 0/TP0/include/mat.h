//---------------------------------------------------------------------
// Arquivo	: mat.h
// Conteudo	: definicoes do TAD MAT 
// Autor	: Erick Sunclair (ericksunclair@ufmg.br)
// Data : 08/11/2021
//---------------------------------------------------------------------

#ifndef MATH
#define MATH

#include "memlog.h"


class Matrix{
	public:
		double** m;			// array 2D que vai armazenar a matriz
		int tamx = -1;		// numero de linhas da matriz
		int tamy = -1;		// numero de colunas da matriz

		// Construtor e Destrutor da classe Matrix
		Matrix(int tx, int ty);
		~Matrix();

		// Outros métodos
		void inicializaMatrizNula();
		void inicializaMatrizAleatoria();
		void imprimeMatriz();
		void escreveElemento(int x, int y, double v);
		double leElemento (int x, int y);
		void copiaMatriz(Matrix* src);
		void somaMatrizes(Matrix* a, Matrix* b);
		void multiplicaMatrizes(Matrix* a, Matrix* b);
		void transpoeMatriz();
};

#endif
