// aca se definen las funciones que se van a ejecutar por los hilos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <global.h>
#include <unistd.h>

void *funcionPeaje(void *threadarg){

    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;

    while(1){

        printf("Peaje numero \n");

        sleep(1);
        pthread_mutex_unlock(&mutex);
        sleep(1);

    }
    printf("Hijo : Termino\n");
    return 0;
}
