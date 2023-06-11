#---------------------------------------------------------------
# Arquivo	: Makefile
# Conteudo	: Makefile para compilacao dos binarios 
#		      do usuario (user) e do servidor (server)
# Autor		: Erick Sunclair (ericksunclair@ufmg.br)
# Data     	: 05/06/2023
#---------------------------------------------------------------

CC = g++
CFLAGS = -std=c++17
MAKEFLAGS += -k		#continua compilacao mesmo se alguma tarefa falhar

all: user server

user: user.cpp
	$(CC) $(CFLAGS) user.cpp -o user -lpthread

server: server.cpp
	$(CC) $(CFLAGS) server.cpp -o server -lpthread

clean:
	rm -f user server