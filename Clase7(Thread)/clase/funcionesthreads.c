// aca se definen las funciones que se van a ejecutar por los hilos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <global.h>
#include <unistd.h>

void *funcionThread(void *parametro)
{
    // logica o tarea del hilo.
    int i;
    printf("Hijo\n");
    for (i = 0; i < CANTIDAD_THREADS; i++)
    {
        pthread_mutex_lock(&mutex);
        printf("Soy el hijo y tengo el mutex\n");
        sleep(1);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    printf("Soy el hijo y espero 10seg\n");
    sleep(10);
    printf("Hijo : Termino\n");
    pthread_exit((void *)"Listo");
}
