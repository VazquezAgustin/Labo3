CC = gcc

CFLAGS = -Wall -std=gnu89 -O3 -pedantic-errors

LIBRARIES = clave.c semaforo.c gestionarch.c

HEADERS = -I./

all: clean main1 productor

main1:
	$(CC) -o main2 main2.c $(LIBRARIES) $(CFLAGS) $(HEADERS)

clean: 
	rm -rf *o main1 productor