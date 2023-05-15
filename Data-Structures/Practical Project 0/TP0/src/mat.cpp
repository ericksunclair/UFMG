//---------------------------------------------------------------------
// Arquivo	: mat.cpp
// Conteudo	: implementacao do TAD MAT 
// Autor	: Erick Sunclair (ericksunclair@ufmg.br)
// Data : 08/11/2021
//---------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <math.h>
#include "mat.h"
#include "memlog.h"
#include "msgassert.h"

// limite superior da inicializacao aleatoria
#define INITRANDOMRANGE 10

Matrix::Matrix(int tx, int ty)
// Descricao: contrutor padrao da classe Matrix - cria uma matriz de tamanho tx X ty
// Entrada: tx, ty
// Saida: nao tem
{
  // verifica se os valores de tx e ty são validos
  erroAssert(tx>0,"Dimensao nula");
  erroAssert(ty>0,"Dimensao nula");

  // inicializa as dimensoes da matriz
  tamx = tx;
  tamy = ty;

  m = (double**) malloc(sizeof(double*)*tamx);   // aloca as linhas da matriz
  // verifica se a alocação dinamica ocorreu corretamente
  erroAssert(m!=NULL,"Erro na alocação dinâmica");
  for (int i=0; i<tamx; i++){
      m[i] = (double*) malloc(sizeof(double)*tamy);  // aloca as colunas pra cada linha da matriz
      // verifica se a alocação dinamica ocorreu corretamente
      erroAssert(m[i]!=NULL,"Erro na alocação dinâmica");
  }

}

Matrix::~Matrix()
// Descricao: destrutor da classe Matrix - destrói a matriz m, que se torna inacessível
// Entrada: nao tem
// Saida: nao tem
{
  for(int i=0; i<tamx; i++){
      delete m[i];
  }
  delete m;

  // torna as dimensoes invalidas
  tamx = -1;
  tamy = -1;
}

void Matrix::inicializaMatrizNula()
// Descricao: inicializa m com valores nulos 
// Entrada: nao tem
// Saida: nao tem
{
  // zera todos os elementos da matriz
  for (int i=0; i<tamx; i++){
    for (int j=0; j<tamy; j++){
      m[i][j] = 0;
      escreveMemLog((long int)(&m[i][j]),sizeof(double));
    }
  }
}

void Matrix::inicializaMatrizAleatoria()
// Descricao: inicializa m com valores aleatorios
// Entrada: nao tem
// Saida: nao tem
{
  // inicializa matriz com valores aletorios entre 0 e INITRANDOMRANGE
  for (int i=0; i<tamx; i++){
    for(int j=0; j<tamy; j++){
      m[i][j] = rand() % INITRANDOMRANGE;
      escreveMemLog((long int)(&m[i][j]),sizeof(double));
    }
  }
}

void Matrix::imprimeMatriz()
// Descricao: imprime a matriz com a identificacao de linhas e colunas
// Entrada: nao tem
// Saida: impressao na saida padrao (stdout) 
{
  // imprime os identificadores de coluna
  std::cout << "  ";
  for(int j=0; j<tamy; j++)
    std::cout << j << " ";
  std::cout << std::endl;

  // imprime as linhas
  for (int i=0; i<tamx; i++){
    std::cout << i << " ";
    for(int j=0; j<tamy; j++){
      std::cout << std::setprecision(4) << m[i][j] << " ";
      leMemLog((long int)(&m[i][j]),sizeof(double));
    }
    std::cout << std::endl;
  }
}

void Matrix::escreveElemento(int x, int y, double v)
// Descricao: atribui o valor v ao elemento (x,y) de m
// Entrada: x, y, v
// Saida: nao tem
{
  // verifica se x e y sao validos
  erroAssert(!((x<0)||(x>=tamx)),"Indice invalido");
  erroAssert(!((y<0)||(y>=tamy)),"Indice invalido");

  m[x][y] = v;
  escreveMemLog((long int)(&m[x][y]),sizeof(double));
}

double Matrix::leElemento (int x, int y)
// Descricao: retorna o elemento (x,y) de m 
// Entrada: x, y
// Saida: m[x][y] 
{
  // verifica se x e y sao validos
  erroAssert(!(x<0)||(x>=tamx),"Indice invalido");
  erroAssert(!(y<0)||(y>=tamy),"Indice invalido");

  leMemLog((long int)(&m[x][y]),sizeof(double));
  return m[x][y];
}

void Matrix::copiaMatriz(Matrix* src)
// Descricao: faz uma copia de src em m
// Entrada: src
// Saida: nao tem
{
  // desaloca a antiga matriz m
  for(int i=0; i<tamx; i++){
      delete m[i];
  }
  delete m;

  // inicializa as novas dimensoes da matriz
  tamx = src->tamx;
  tamy = src->tamy;

  // realoca a matriz com as dimensões de src
  m = (double**) malloc(sizeof(double*)*tamx);   // aloca as linhas da matriz
  // verifica se a alocação dinamica ocorreu corretamente
  erroAssert(m!=NULL,"Erro na alocação dinâmica");
  for (int i=0; i<tamx; i++){
      m[i] = (double*) malloc(sizeof(double)*tamy);  // aloca as colunas pra cada linha da matriz
      // verifica se a alocação dinamica ocorreu corretamente
      erroAssert(m[i]!=NULL,"Erro na alocação dinâmica");
  }

  // inicializa a matriz m como nula
  inicializaMatrizNula();
  // copia os elementos da matriz src
  for (int i=0; i<src->tamx; i++){
    for (int j=0; j<src->tamy; j++){
      m[i][j] = src->m[i][j];
      leMemLog((long int)(&(src->m[i][j])),sizeof(double));
      escreveMemLog((long int)(&m[i][j]),sizeof(double));
    }
  }
}

void Matrix::somaMatrizes(Matrix* a, Matrix* b)
// Descricao: soma as matrizes a e b e armazena o resultado em m
// Entrada: a, b
// Saida: nao tem
{
  // verifica se as dimensoes das matrizes a e b sao as mesmas
  erroAssert(a->tamx==b->tamx,"Dimensoes incompativeis");
  erroAssert(a->tamy==b->tamy,"Dimensoes incompativeis");

  // desaloca a antiga matriz m
  for(int i=0; i<tamx; i++){
      delete m[i];
  }
  delete m;

  // inicializa as novas dimensoes da matriz
  tamx = a->tamx;
  tamy = a->tamy;

  // realoca a matriz com as dimensões de a e b
  m = (double**) malloc(sizeof(double*)*tamx);   // aloca as linhas da matriz
  // verifica se a alocação dinamica ocorreu corretamente
  erroAssert(m!=NULL,"Erro na alocação dinâmica");
  for (int i=0; i<tamx; i++){
      m[i] = (double*) malloc(sizeof(double)*tamy);  // aloca as colunas pra cada linha da matriz
      // verifica se a alocação dinamica ocorreu corretamente
      erroAssert(m[i]!=NULL,"Erro na alocação dinâmica");
  }

  // inicializa a matriz m como nula
  inicializaMatrizNula();

  // faz a soma elemento a elemento
  for (int i=0; i<a->tamx; i++){
    for(int j=0; j<a->tamy; j++){
      m[i][j] = a->m[i][j] + b->m[i][j];
      leMemLog((long int)(&(a->m[i][j])),sizeof(double));
      leMemLog((long int)(&(b->m[i][j])),sizeof(double));
      escreveMemLog((long int)(&m[i][j]),sizeof(double));
    }
  }
}

void Matrix::multiplicaMatrizes(Matrix* a, Matrix* b)
// Descricao: multiplica as matrizes a e b e armazena o resultado em m
// Entrada: a, b
// Saida: nao tem
{
  // verifica a compatibilidade das dimensoes 
  erroAssert(a->tamy==b->tamx,"Dimensoes incompativeis");

  // desaloca a antiga matriz m
  for(int i=0; i<tamx; i++){
      delete m[i];
  }
  delete m;

  // inicializa as novas dimensoes da matriz
  tamx = a->tamx;
  tamy = b->tamy;

  // realoca a matriz com o número de linhas de a e numero de colunas de b
  m = (double**) malloc(sizeof(double*)*tamx);   // aloca as linhas da matriz
  // verifica se a alocação dinamica ocorreu corretamente
  erroAssert(m!=NULL,"Erro na alocação dinâmica");
  for (int i=0; i<tamx; i++){
      m[i] = (double*) malloc(sizeof(double)*tamy);  // aloca as colunas pra cada linha da matriz
      // verifica se a alocação dinamica ocorreu corretamente
      erroAssert(m[i]!=NULL,"Erro na alocação dinâmica");
  }

  // inicializa a matriz m como nula
  inicializaMatrizNula();

  // realiza a multiplicacao de matrizes
  for (int i=0; i<tamx;i++){
    for (int j=0; j<tamy;j++){
      for (int k=0; k<a->tamy;k++){
        m[i][j] += a->m[i][k]*b->m[k][j];
        leMemLog((long int)(&(a->m[i][k])),sizeof(double));
        leMemLog((long int)(&(b->m[k][j])),sizeof(double));
        escreveMemLog((long int)(&m[i][j]),sizeof(double));
      }
    }
  }
}

void Matrix::transpoeMatriz()
// Descricao: transpoe a matriz m
// Entrada: nao tem
// Saida: nao tem
{
  // aloca uma matriz auxiliar com o número de linhas e de colunas trocados
  double** t;
  t = (double**) malloc(sizeof(double*)*tamy);   // aloca as linhas da matriz
  // verifica se a alocação dinamica ocorreu corretamente
  erroAssert(t!=NULL,"Erro na alocação dinâmica");
  for (int i=0; i<tamy; i++){
      t[i] = (double*) malloc(sizeof(double)*tamx);  // aloca as colunas pra cada linha da matriz
      // verifica se a alocação dinamica ocorreu corretamente
      erroAssert(t[i]!=NULL,"Erro na alocação dinâmica");
  }

  // inicializa a matriz t como nula
  for (int i=0; i<tamy; i++){
    for (int j=0; j<tamx; j++){
      t[i][j] = 0;
      escreveMemLog((long int)(&t[i][j]),sizeof(double));
    }
  }

  // transpoe os valores de m em t
  for (int i=0; i<tamx; i++){
    for (int j=0; j<tamy; j++){
      t[j][i] = m[i][j];
      leMemLog((long int)(&m[i][j]),sizeof(double));
      escreveMemLog((long int)(&t[j][i]),sizeof(double));
    }
  }

  // m passa a apontar pra onde t foi definida
  m = t;
  // inverte as dimensoes da matriz transposta
  tamx += tamy;
  tamy = tamx-tamy;
  tamx -= tamy;

}