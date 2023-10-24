CC = gcc

CFLAGS = -Wall -std=gnu89 -O3 -pedantic-errors

LIBRARIES = clave.c semaforo.c memoria.c funcionesthreads.c

HEADERS = -I./

all: clean main1

main1:
	$(CC) -o main main.c $(LIBRARIES) $(CFLAGS) $(HEADERS)

clean: 
	rm -rf *o main *.dat