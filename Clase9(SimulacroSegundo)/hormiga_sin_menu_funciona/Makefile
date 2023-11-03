CC = gcc
CFLAGS = -Wall -Wextra -std=gnu89 -pedantic-errors -O3 -pthread

TARGET1 = reina
SRC1 = reina.c hormiga.c mensajes.c clave.c global.c
HDR = hormiga.h mensajes.h clave.h global.h

all: clean $(TARGET1)

$(TARGET1): $(SRC1) $(HDR)
	$(CC) $(CFLAGS) $(SRC1) -o $(TARGET1)
clean:
	rm -f $(TARGET1)
