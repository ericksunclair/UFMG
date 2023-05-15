#---------------------------------------------------------------
# Arquivo	: Makefile
# Conteudo	: Makefile para compilacao dos binarios 
#		      do cliente e do servidor
# Autor		: Erick Sunclair (ericksunclair@ufmg.br)
# Data     	: 14/05/2023
#---------------------------------------------------------------

CC = g++
CFLAGS = -std=c++17
MAKEFLAGS += -k		#continua compilacao mesmo se alguma tarefa falhar

all: client server

client: client.cpp
	$(CC) $(CFLAGS) client.cpp -o client

server: server.cpp
	$(CC) $(CFLAGS) server.cpp -o server

clean:
	rm -f client server