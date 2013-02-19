# Esto es un comentario. 
# La variable CC se utiliza para especificar el compilador a utilizar
CC=g++
# La variable CFLAGS se utiliza para pasarle opciones al compilador 
CFLAGS=-c -Wall -o

all: main

main: ram.o main.o instruccion.o diccionario_etiquetas.o cintalectura.o cintaescritura.o bancoregistros.o
	$(CC) compiled/ram.o compiled/main.o compiled/instruccion.o compiled/diccionario_etiquetas.o compiled/cintaescritura.o compiled/cintalectura.o compiled/bancoregistros.o -o ram

main.o: lib/main.cpp
	$(CC) $(CFLAGS) compiled/main.o lib/main.cpp

ram.o: lib/ram.cpp
	$(CC) $(CFLAGS) compiled/ram.o lib/ram.cpp

instruccion.o: lib/instruccion.cpp
	$(CC) $(CFLAGS) compiled/instruccion.o lib/instruccion.cpp

diccionario_etiquetas.o: lib/diccionario_etiquetas.cpp
	$(CC) $(CFLAGS) compiled/diccionario_etiquetas.o lib/diccionario_etiquetas.cpp

cintalectura.o: lib/cintalectura.cpp
	$(CC) $(CFLAGS) compiled/cintalectura.o lib/cintalectura.cpp

cintaescritura.o: lib/cintaescritura.cpp
	$(CC) $(CFLAGS) compiled/cintaescritura.o lib/cintaescritura.cpp

bancoregistros.o: lib/bancoregistros.cpp
	$(CC) $(CFLAGS) compiled/bancoregistros.o lib/bancoregistros.cpp

