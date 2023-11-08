CC = gcc

CFLAGS = -Wall -std=gnu89 -O3 -pedantic-errors

LIBRARIES = clave.c semaforo.c gestionarch.c memoria.c colamensaje.c funcionthreads.c

HEADERS = -I./

all: clean main main2

main:
	$(CC) -o 1panel 1panel.c $(LIBRARIES) $(CFLAGS) $(HEADERS)

main2:
	$(CC) -o 2votantes 2votantes.c $(LIBRARIES) $(CFLAGS) $(HEADERS)

clean: 
	rm -rf *o 1_panel 2_votantes *.dat