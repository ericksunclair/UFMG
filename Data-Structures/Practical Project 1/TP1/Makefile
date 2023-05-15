#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa do escalonador de urls
# Autor		: Erick Sunclair (ericksunclair@ufmg.br)
# Data 		: 28/11/2021
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
OBJS = $(OBJ)/main.o $(OBJ)/item_url.o $(OBJ)/lista_urls.o
HDRS = $(INC)/item_url.h $(INC)/lista_urls.h
CFLAGS = -Wall -c -I$(INC)

EXE = $(BIN)/main

all: $(EXE)
	$(EXE) *.txt

$(BIN)/main: $(OBJS)
	$(CC) -o $(BIN)/main $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/lista_urls.o: $(HDRS) $(SRC)/lista_urls.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/lista_urls.o $(SRC)/lista_urls.cpp

$(OBJ)/item_url.o: $(HDRS) $(SRC)/item_url.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/item_url.o $(SRC)/item_url.cpp
	
clean:
	rm $(EXE) $(OBJS) 
