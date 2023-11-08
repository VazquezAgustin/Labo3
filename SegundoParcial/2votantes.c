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
#include <funcionthreads.h>

int main(int arg, char *argv[])
{   
    // memoria y semaforo
    int id_memoria;
    dato_flag *memoria = NULL;
    int id_cola_mensajes;
    pthread_t *idThread = NULL;
    pthread_attr_t atributos;
    datosThread *datos_thread = NULL;
    //comunes
    int index_creacion_threads = 0;

    pthread_mutex_init(&mutex, NULL);

    memoria = (dato_flag*)creo_memoria(sizeof(dato_flag), &id_memoria, CLAVE_BASE);
    idThread = (pthread_t *)malloc(sizeof(pthread_t)*CANTIDAD_VOTANTES); //primero 1 thread, dsp pruebo varios
    pthread_attr_init(&atributos); 
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);
    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

    datos_thread = (datosThread *)malloc(sizeof(datosThread)*CANTIDAD_VOTANTES);

    for (index_creacion_threads=0; index_creacion_threads<CANTIDAD_VOTANTES; index_creacion_threads++){
        datos_thread[index_creacion_threads].idThread = MSG_VOTANTE + index_creacion_threads;
        datos_thread[index_creacion_threads].id_cola_mensajes = id_cola_mensajes;
        datos_thread[index_creacion_threads].output_evento = 0;
        printf("idVotante: %d\tid_cola_mensajes: %d \n", datos_thread[index_creacion_threads].idThread, datos_thread[index_creacion_threads].id_cola_mensajes);
        pthread_create(&idThread[index_creacion_threads], &atributos, funcionThread, &datos_thread[index_creacion_threads]);
    }

    for (index_creacion_threads=0; index_creacion_threads<CANTIDAD_VOTANTES; index_creacion_threads++){
        pthread_join (idThread[index_creacion_threads], NULL);
    }

    memoria->terminar = 1;

    free(idThread);
    borrar_mensajes(id_cola_mensajes);
    msgctl (id_cola_mensajes, IPC_RMID, NULL);

    return 0;
}
