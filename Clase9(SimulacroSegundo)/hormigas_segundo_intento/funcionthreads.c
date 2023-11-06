// aca se definen las funciones que se van a ejecutar por los hilos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <global.h>
#include <unistd.h>
#include <colamensaje.h>

void *funcionThread(void *threadarg){

    // memoria y semaforo
    int id_cola_mensajes;
    mensaje msg;
    int idThread = 0;
    datosThread *datos_thread = (datosThread*) threadarg;
    // comun 
    int termino = 0;
    int numero_aleatorio = 0;
    int mensaje_recibido = 0;

    srand(time(NULL));

    // paso en limpio inputs
    idThread = datos_thread->idThread;
    id_cola_mensajes = datos_thread->id_cola_mensajes;

    // logica
    while (termino == 0)
    {
        usleep(500 * 1000);
        mensaje_recibido = recibir_mensaje(id_cola_mensajes, idThread, &msg, 1);
        if (mensaje_recibido > 0){
            printf("Thread %d Recibiendo pedido de reina \n", idThread);
            pthread_mutex_lock(&mutex);
            
                numero_aleatorio = rand() % 5;
                termino = 1;
            
                printf("Thread %d obtuvo %d cantidad de material %d \n", idThread, msg.tipo_insumo, numero_aleatorio);
                usleep(2000 * 1000);
                enviar_mensaje(id_cola_mensajes, MSG_REINA, idThread, msg.tipo_insumo, numero_aleatorio);
            pthread_mutex_unlock(&mutex);
        }
    }

    return 0;
}
