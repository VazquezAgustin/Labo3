CC = gcc

CFLAGS = -Wall -std=gnu89 -O3 -pedantic-errors

LIBRARIES = clave.c semaforo.c gestionarch.c

HEADERS = -I./

all: clean main1 productor

main1:
	$(CC) -o main1 main1.c $(LIBRARIES) $(CFLAGS) $(HEADERS)

productor:
	$(CC) -o productor productor.c $(LIBRARIES) $(CFLAGS) $(HEADERS)

clean: 
	rm -rf *o main1 productor *.dat