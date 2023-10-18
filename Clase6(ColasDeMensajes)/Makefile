CC = gcc

CFLAGS = -Wall -std=gnu89 -O3 -pedantic-errors

LIBRARIES = clave.c semaforo.c gestionarch.c memoria.c colamensaje.c

HEADERS = -I./

all: clean main1 main2

main1:
	$(CC) -o banco banco.c $(LIBRARIES) $(CFLAGS) $(HEADERS)

main2:
	$(CC) -o cajero cajero.c $(LIBRARIES) $(CFLAGS) $(HEADERS)

clean: 
	rm -rf *o banco cajero *.dat