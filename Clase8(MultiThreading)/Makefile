CC = gcc

CFLAGS = -Wall -std=gnu89 -O3 -pedantic-errors

LIBRARIES = clave.c semaforo.c gestionarch.c memoria.c

HEADERS = -I./

all: clean main main2

main:
	$(CC) -o peaje peaje.c $(LIBRARIES) $(CFLAGS) $(HEADERS)

main2:
	$(CC) -o autos autos.c $(LIBRARIES) $(CFLAGS) $(HEADERS)

clean: 
	rm -rf *o peaje autos *.dat