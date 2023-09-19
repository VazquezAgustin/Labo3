CC = gcc

CFLAGS = -Wall -std=gnu89 -O3 -pedantic-errors

LIBRARIES = clave.c semaforo.c gestionarch.c

HEADERS = -I./

all: clean main1 main2

main1:
	$(CC) -o main1 main1.c $(LIBRARIES) $(CFLAGS) $(HEADERS)

main2:
	$(CC) -o caja caja.c $(LIBRARIES) $(CFLAGS) $(HEADERS)

clean: 
	rm -rf *o main1 main2 *.dat