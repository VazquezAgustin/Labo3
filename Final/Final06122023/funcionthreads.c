// aca se definen las funciones que se van a ejecutar por los hilos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <global.h>
#include <unistd.h>
#include <colamensaje.h>

void *funcionThreadNormal(void *threadarg){

    // memoria y semaforo
    int id_cola_mensajes;
    int idThread = 0;
    datosThread *datos_thread = (datosThread*) threadarg;
    //comunes
    int cantidad = 0;
    int index_vueltas = 0;
    int minimo = 0;
    int maximo = 0;

    // paso en limpio inputs
    idThread = datos_thread->idThread;
    id_cola_mensajes = datos_thread->id_cola_mensajes;

    srand(time(NULL));

    // definir maximo y minimo segun tipo
    switch (idThread)
    {
    case MSG_RAYOS:
        minimo = 0;
        maximo = 4;
        break;
    
    case MSG_TRUENOS:
        minimo = 1;
        maximo = 3;
        break;
    
    case MSG_RELAMPAGOS:
        minimo = 0;
        maximo = 1;
        break;
    
    default:
        printf("tipo de evento no reconocido");
        break;
    }

    for (index_vueltas = 0; index_vueltas < CANTIDAD_EVENTOS_POR_THREADS; index_vueltas++)
    {
        pthread_mutex_lock(&mutex_proceso_2);
            cantidad = (rand() % (maximo - minimo + 1)) + minimo;
            printf("Thread %d genero cantidad %d \n", idThread, cantidad);
            enviar_mensaje(id_cola_mensajes, MSG_PANEL, idThread, EVT_INFO, cantidad);
        pthread_mutex_unlock(&mutex_proceso_2);
        usleep(600 * 1000);
    }

    return 0;
}

void *funcionThreadLluvia(void *threadarg){

    printf("Comenzo a llover");
    return 0;
}
