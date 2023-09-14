CC = gcc

CFLAGS = -Wall -std=gnu89 -O3 -pedantic-errors

HEADERS = -I./

all: clean main1 productora

main1:
	$(CC) -o main1 main1.c clave.c semaforo.c gestionarch.c $(CFLAGS) $(HEADERS)

productora:
	$(CC) -o productora productora.c clave.c semaforo.c gestionarch.c $(CFLAGS) $(HEADERS)

clean: 
	rm -rf *o main1 productora pedidos.dat 