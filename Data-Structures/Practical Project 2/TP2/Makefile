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
OBJS = $(OBJ)/main.o $(OBJ)/heap.o $(OBJ)/fita.o
HDRS = $(INC)/heap.h $(INC)/fita.h $(INC)/entidade.h
CFLAGS = -Wall -c -I$(INC)

EXE = $(BIN)/main

all: $(EXE)
# nome arquivo de entrada | nome arquivo de saída | num de entidades por rodada
	$(EXE) entrada.txt saida.txt 15
# observaçao: arquivo de entrada não pode ter espaço ou /n no fim

$(BIN)/main: $(OBJS)
	$(CC) -o $(BIN)/main $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/heap.o: $(HDRS) $(SRC)/heap.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/heap.o $(SRC)/heap.cpp

$(OBJ)/fita.o: $(HDRS) $(SRC)/fita.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/fita.o $(SRC)/fita.cpp

clean:
	rm $(EXE) $(OBJS) 
