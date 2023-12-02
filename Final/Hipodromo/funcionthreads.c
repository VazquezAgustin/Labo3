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
    int idThread = 0;
    mensaje msg;
    datosThread *datos_thread = (datosThread*) threadarg;
    //comunes
    int mensaje_recibido = 0;
    int inicio = 0;
    int metros_totales = 0;
    int metros = 0;
    
    // paso en limpio inputs
    idThread = datos_thread->idThread;
    id_cola_mensajes = datos_thread->id_cola_mensajes;

    srand(time(NULL));

    while (inicio == 0)
    {
        mensaje_recibido = recibir_mensaje(id_cola_mensajes, idThread, &msg, 1);
        if (mensaje_recibido > 0 && msg.int_evento == EVT_INICIO){
            inicio = 1;
            metros_totales = msg.metros;
        }
    }

    printf("post inicio %d \n", idThread);
    while (msg.int_evento != EVT_CRUZARON_EL_DISCO)
    {
        pthread_mutex_lock(&mutex);
        metros = rand() % 41 + 10;
        printf("corri %d metros\n", metros);

        usleep(200 * 1000);
        enviar_mensaje(id_cola_mensajes, MSG_HIPODROMO , idThread, EVT_METROS, metros);

        pthread_mutex_unlock(&mutex);
        usleep(200 * 1000);
        usleep(200 * 1000);
        usleep(200 * 1000);
        mensaje_recibido = recibir_mensaje(id_cola_mensajes, idThread, &msg, 0);
    }
    
    if (msg.int_evento == EVT_CRUZARON_EL_DISCO)
    {
        datos_thread->output_thread = msg.metros; //guardo el ganador
    }
    
    printf("Thread %d termino \n", idThread);

    return 0;
}
