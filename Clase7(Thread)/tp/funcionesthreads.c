// aca se definen las funciones que se van a ejecutar por los hilos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <global.h>
#include <unistd.h>

void *funcionThread(void *threadarg){

    int i;
    int random_number;
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;

    printf("numero a adivinar es %d \n", my_data->numero_aleatorio);

    for (i = 0; i < my_data->cantidad_threads; i++){
        
        while(my_data->alguien_acerto == 0){

            printf("Hijo\n");
            for (i = 0; i < my_data->cantidad_threads; i++)
            {
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
            printf("Soy el hijo y espero 10ms\n");
            usleep(100000);
            printf("Hijo : Termino\n");
        }

    }

    return 0;
}
