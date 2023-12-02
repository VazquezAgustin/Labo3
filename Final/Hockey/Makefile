CC = gcc

CFLAGS = -Wall -std=gnu89 -O3 -pedantic-errors

LIBRARIES = clave.c semaforo.c gestionarch.c memoria.c colamensaje.c funcionthreads_arquero.c funcionthreads_jugador.c

HEADERS = -I./

all: clean main

main:
	$(CC) -o equipo1 equipo1.c $(LIBRARIES) $(CFLAGS) $(HEADERS)

# main2:
#  	$(CC) -o equipo2 equipo2.c $(LIBRARIES) $(CFLAGS) $(HEADERS)

clean: 
	rm -rf *o main *.dat