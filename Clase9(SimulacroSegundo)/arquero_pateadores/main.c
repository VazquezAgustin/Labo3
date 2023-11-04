// arquero
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <memoria.h>
#include <semaforo.h>
#include <time.h>
#include <gestionarch.h>
#include <global.h>
#include <colamensaje.h>


int main(int arg, char *argv[])
{   
    // memoria y semaforo
    pthread_t* idHilo;
    pthread_attr_t atributos;
    int id_cola_mensajes;
    mensaje msg;
    //comunes

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    borrar_mensajes(id_cola_mensajes);

    recibir_mensaje(id_cola_mensajes, MSG_ARQUERO, &msg);

    return 0;
}
