#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa matop
# Autor		: Wagner Meira Jr. (meira@dcc.ufmg.br)
# Histórico	: 2021-10-18 - arquivo criado
#		: 2021-10-21 - estrutura de diretórios
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#		: make clean - remove objetos e executável
#---------------------------------------------------------------------

CC = g++
CFLAGS = -Wall -c
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/matop.o $(OBJ)/mat.o $(OBJ)/memlog.o
HDRS = $(INC)/mat.h $(INC)/memlog.h $(INC)/msgassert.h
CFLAGS = -Wall -c -I$(INC)

EXE = $(BIN)/matop

all: $(EXE)
	$(EXE) -s -p ./tmp/somalog.out -l -x 4 -y 5
	$(EXE) -m -p ./tmp/multlog.out -l -x 5 -y 5
	$(EXE) -t -p ./tmp/transplog.out -l -x 5 -y 4

$(BIN)/matop: $(OBJS)
	$(CC) -o $(BIN)/matop $(OBJS) $(LIBS)

$(OBJ)/matop.o: $(HDRS) $(SRC)/matop.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/matop.o $(SRC)/matop.cpp

$(OBJ)/mat.o: $(HDRS) $(SRC)/mat.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/mat.o $(SRC)/mat.cpp

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.cpp
	
clean:
	rm $(EXE) $(OBJS) 
