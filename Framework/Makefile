CC = gcc

CFLAGS = -Wall -std=gnu89 -O3 -pedantic-errors

LIBRARIES = clave.c semaforo.c gestionarch.c memoria.c colamensaje.c funcionthreads.c

HEADERS = -I./

all: clean main run_script

main:
	$(CC) -o main main.c $(LIBRARIES) $(CFLAGS) $(HEADERS)

# main2:
# 	$(CC) -o cajero cajero.c $(LIBRARIES) $(CFLAGS) $(HEADERS)

clean: 
	rm -rf *o main *.dat

run_script:
	bash cleanupmemory.sh