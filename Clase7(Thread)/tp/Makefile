CC = gcc

CFLAGS = -Wall -std=gnu89 -O3 -pedantic-errors

LIBRARIES = clave.c semaforo.c gestionarch.c memoria.c colamensaje.c funcionesthreads.c

HEADERS = -I./

all: clean main1

main1:
	$(CC) -o main main.c $(LIBRARIES) $(CFLAGS) $(HEADERS)

clean: 
	rm -rf *o main *.dat