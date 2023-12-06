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
    int id_cola_mensajes;
    pthread_t *idThread = NULL;
    pthread_attr_t atributos;
    datosThread *datos_thread = NULL;
    //comunes
    int id_memoria_inicio = 0;
    int id_memoria_inicio_lluvia = 0;
    dato_inicio *memoria_inicio = NULL;
    dato_inicio *memoria_inicio_lluvia = NULL;
    int index_creacion_threads = 0;
    int iniciar = 0;

    // inicializaciones
    memoria_inicio = (dato_inicio*)creo_memoria(sizeof(dato_inicio), &id_memoria_inicio, CLAVE_BASE);
    memoria_inicio_lluvia = (dato_inicio*)creo_memoria(sizeof(dato_inicio), &id_memoria_inicio_lluvia, CLAVE_BASE + 1000);
    idThread = (pthread_t *)malloc(sizeof(pthread_t)*CANTIDAD_THREADS);
    pthread_attr_init(&atributos); 
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);
    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE + 400);

    datos_thread = (datosThread *)malloc(sizeof(datosThread)*CANTIDAD_THREADS);

    while (iniciar == 0)
    {
        if (memoria_inicio->iniciar == 1)
        {
            printf("proceso 1 iniciado, comenzando \n");
            iniciar = 1;
        }
        else
        {
            printf("esperando proceso 1...\n");
            sleep(1);
        }
    }
    
    // comenzar rayos truenos y relampagos, NO lluvia
    for (index_creacion_threads=0; index_creacion_threads<3; index_creacion_threads++){
        datos_thread[index_creacion_threads].idThread = MSG_RAYOS + index_creacion_threads;
        datos_thread[index_creacion_threads].id_cola_mensajes = id_cola_mensajes;
        printf("idThread: %d\tid_cola_mensajes: %d \n", datos_thread[index_creacion_threads].idThread, datos_thread[index_creacion_threads].id_cola_mensajes);
        pthread_create(&idThread[index_creacion_threads], &atributos, funcionThreadNormal, &datos_thread[index_creacion_threads]);
    }

    // cuando se detecta 1 trueno se activa la lluvia
    while (memoria_inicio_lluvia->iniciar == 0)
    {
        printf("Todavia no se detectaron truenos\n");
        sleep(3);
    }
    datos_thread[3].idThread = MSG_LLUVIA;
    datos_thread[3].id_cola_mensajes = id_cola_mensajes;
    printf("idThread: %d\tid_cola_mensajes: %d \n", datos_thread[3].idThread, datos_thread[3].id_cola_mensajes);
    pthread_create(&idThread[3], &atributos, funcionThreadLluvia, &datos_thread[3]);

    for (index_creacion_threads=0; index_creacion_threads<CANTIDAD_THREADS; index_creacion_threads++){
        pthread_join (idThread[index_creacion_threads], NULL);
    }
    
    // avisar a proceso 1 que debe terminar
    memoria_inicio->iniciar = 0;

    pthread_mutex_destroy(&mutex_proceso_2);
    free(idThread);

    return 0;
}
