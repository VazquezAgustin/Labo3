CC = gcc

CFLAGS = -Wall -std=gnu89 -O3 -pedantic-errors

LIBRARIES = clave.c semaforo.c gestionarch.c memoria.c colamensaje.c funcionthreads.c

HEADERS = -I./

all: clean main main2

main:
	$(CC) -o 1arquero 1arquero.c $(LIBRARIES) $(CFLAGS) $(HEADERS)

main2:
	$(CC) -o 2pateadores 2pateadores.c $(LIBRARIES) $(CFLAGS) $(HEADERS)

clean: 
	rm -rf *o 1arquero 2pateadores *.dat