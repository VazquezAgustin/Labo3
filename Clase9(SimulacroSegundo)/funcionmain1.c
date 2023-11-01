// aca se definen las funciones que se van a ejecutar por los hilos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <global.h>
#include <unistd.h>

void *funcionPeaje(void *threadarg){

    int random_number;
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;

    while(1){

        printf("Peaje numero \n");

        pthread_mutex_lock(&mutex);
        printf("Soy el hijo y tengo el mutex\n");
        random_number = (rand() % 99) + 1;
        printf("numero %d - a acertar es %d \n", random_number, my_data->numero_aleatorio);
        if(random_number == my_data->numero_aleatorio){
            my_data->alguien_acerto = 1;
            printf("acerte !!!! \n");
        }
        sleep(1);
        pthread_mutex_unlock(&mutex);
        sleep(1);

    }
    printf("Hijo : Termino\n");
    return 0;
}
