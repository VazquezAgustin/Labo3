// aca se definen las funciones que se van a ejecutar por los hilos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <global.h>
#include <unistd.h>
#include <colamensaje.h>

void *funcionThread(void *threadarg)
{

    // memoria y semaforo
    int id_cola_mensajes;
    mensaje msg;
    int idThread = 0;
    datosThread *datos_thread = (datosThread*) threadarg;
    //comunes
    int mensaje_recibido = 0;
    int termino = 0;

    // paso en limpio inputs
    idThread = datos_thread->idThread;
    id_cola_mensajes = datos_thread->id_cola_mensajes;


    pthread_mutex_lock(&mutex);
        printf("Thread %d realizando tiro \n", idThread);
        usleep(500 * 1000);
        enviar_mensaje(id_cola_mensajes, MSG_ARQUERO, idThread, EVT_TIRO);
    pthread_mutex_unlock(&mutex);

    // logica
    while (termino == 0)
    {
        usleep(500 * 1000);
        printf("Thread %d Recibiendo resultado de tiro \n", idThread);
        mensaje_recibido = recibir_mensaje(id_cola_mensajes, idThread, &msg);
        if (mensaje_recibido > 0){
            pthread_mutex_lock(&mutex);
                
                switch (msg.int_evento)
                {
                case EVT_GOL:
                    printf("GOOOOL \n");
                    break;
                
                default:
                    printf("UFFFFFFF \n");
                    break;
                }
        }
        pthread_mutex_unlock(&mutex);
    }
    datos_thread->output_evento = msg.int_evento;

    pthread_exit ((void*)0);
}
