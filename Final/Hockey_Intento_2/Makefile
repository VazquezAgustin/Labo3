CC = gcc

CFLAGS = -Wall -std=gnu89 -O3 -pedantic-errors

LIBRARIES = clave.c semaforo.c gestionarch.c memoria.c colamensaje.c funcionthreads.c

HEADERS = -I./

all: clean main main2 run_script

main:
	$(CC) -o equipo1 equipo1.c $(LIBRARIES) $(CFLAGS) $(HEADERS)

main2:
	$(CC) -o equipo2 equipo2.c $(LIBRARIES) $(CFLAGS) $(HEADERS)

clean: 
	rm -rf *o equipo1 equipo2 *.dat

run_script:
	bash cleanupmemory.sh