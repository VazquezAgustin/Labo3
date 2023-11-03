#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include "global.h"
#include "mensajes.h"

void *threadHormiga(void *parametro){
    int idHormiga, id_cola_mensajes, recibido, done= 0;
    mensaje mensaje;

    datosHormiga *datos_hormiga = (datosHormiga*) parametro;
    idHormiga = datos_hormiga->idHormiga;
    id_cola_mensajes = datos_hormiga->id_cola_mensajes;

    while (done == 0){

        pthread_mutex_lock(&mutex);
            recibido = recibir_mensaje_no_bloqueante(id_cola_mensajes, idHormiga, &mensaje);
        pthread_mutex_unlock(&mutex);

        if (recibido > 0){
            
            if (mensaje.insumo != NADA){

                mensaje.cantidad = MINIMO_INSUMOS + (rand() % (MAXIMO_INSUMOS - MINIMO_INSUMOS + 1));
                printf("\nHormiga id: %d junto %d del insumo %d", idHormiga, mensaje.cantidad, mensaje.insumo);
                printf("\n");

                usleep(INTERVALO * 1000);

                pthread_mutex_lock(&mutex);
                    enviar_mensaje(id_cola_mensajes, MSG_REINA, idHormiga, mensaje.insumo, mensaje.cantidad);
                pthread_mutex_unlock(&mutex);

            }

        }

    }
    printf("\nHormiga id: %d termina", idHormiga);
    printf("\n");
    pthread_exit((void*)0);
}
