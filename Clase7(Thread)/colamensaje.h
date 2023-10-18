#ifndef _COLAMENSAJE
#define _COLAMENSAJE

#include "global.h"

int creo_id_cola_mensajes(int);

int enviar_mensaje(int, long, int, int, char *);

int recibir_mensaje(int, long, mensaje*);

int borrar_mensajes(int);

#endif
