#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa do algoritmo de ordenação
# Autor		: Erick Sunclair (ericksunclair@ufmg.br)
# Data 		: 12/01/2021
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#			: make clean - remove objetos e executável
#---------------------------------------------------------------------

CC = g++
CFLAGS = -Wall -c
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o $(OBJ)/hash.o
HDRS = $(INC)/hash.h
CFLAGS = -Wall -c -std=c++17 -I$(INC)

EXE = $(BIN)/main

all: $(EXE)

	$(EXE) -i consultas/consulta1.txt -o rankings/ranking1.txt -c colecao_small -s stopwords.txt
	$(EXE) -i consultas/consulta2.txt -o rankings/ranking2.txt -c colecao_small -s stopwords.txt
	$(EXE) -i consultas/consulta3.txt -o rankings/ranking3.txt -c colecao_small -s stopwords.txt
	$(EXE) -i consultas/consulta4.txt -o rankings/ranking4.txt -c colecao_small -s stopwords.txt
	$(EXE) -i consultas/consulta5.txt -o rankings/ranking5.txt -c colecao_small -s stopwords.txt
	$(EXE) -i consultas/consulta6.txt -o rankings/ranking6.txt -c colecao_small -s stopwords.txt
	$(EXE) -i consultas/consulta7.txt -o rankings/ranking7.txt -c colecao_small -s stopwords.txt
	$(EXE) -i consultas/consulta8.txt -o rankings/ranking8.txt -c colecao_small -s stopwords.txt
	$(EXE) -i consultas/consulta9.txt -o rankings/ranking9.txt -c colecao_small -s stopwords.txt
	$(EXE) -i consultas/consulta10.txt -o rankings/ranking10.txt -c colecao_small -s stopwords.txt

$(BIN)/main: $(OBJS)
	$(CC) -pg -o $(BIN)/main $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) -pg $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/hash.o: $(HDRS) $(SRC)/hash.cpp
	$(CC) -pg $(CFLAGS) -o $(OBJ)/hash.o $(SRC)/hash.cpp

prof:
	gprof $(BIN)/main.exe gmon.out > analise.txt

clean:
	rm $(EXE) $(OBJS)
	rm corpus_tratado/*