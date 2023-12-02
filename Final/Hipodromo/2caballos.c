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
    int id_cola_mensajes;
    pthread_t *idThread = NULL;
    pthread_attr_t atributos;
    datosThread *datos_thread = NULL;
    //comunes
    int index_creacion_threads = 0;
    int cantidad_caballos = 0;

    pthread_mutex_init(&mutex, NULL);

    if (arg == 2){
        cantidad_caballos = atoi(argv[1]);
    }else
    {
        printf("Uso: Ingresar numero de caballos (max 40) \n");
        exit(-1);
    }

    idThread = (pthread_t *)malloc(sizeof(pthread_t)*cantidad_caballos);
    pthread_attr_init(&atributos); 
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);
    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

    datos_thread = (datosThread *)malloc(sizeof(datosThread)*cantidad_caballos);

    for (index_creacion_threads=0; index_creacion_threads<cantidad_caballos; index_creacion_threads++){
        datos_thread[index_creacion_threads].idThread = MSG_CABALLO + index_creacion_threads;
        datos_thread[index_creacion_threads].id_cola_mensajes = id_cola_mensajes;
        printf("idCaballo: %d\tid_cola_mensajes: %d \n", datos_thread[index_creacion_threads].idThread, datos_thread[index_creacion_threads].id_cola_mensajes);
        pthread_create(&idThread[index_creacion_threads], &atributos, funcionThread, &datos_thread[index_creacion_threads]);
    }

    for (index_creacion_threads=0; index_creacion_threads<cantidad_caballos; index_creacion_threads++){
        pthread_join (idThread[index_creacion_threads], NULL);
        printf("Ganador fue caballo %d \n", datos_thread->output_thread);
    }

    free(idThread);

    return 0;
}
