#ifndef _COLAMENSAJE
#define _COLAMENSAJE

#include "global.h"

int creo_id_cola_mensajes(int);
int recibir_mensaje(int, long, mensaje *, int);
int enviar_mensaje(int, long, int, int/*, int, int, char * */);
int borrar_mensajes(int);

#endif
