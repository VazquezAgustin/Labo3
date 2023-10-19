#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <global.h>
#include <funcionesthreads.h>
#include <unistd.h>

int main()
{
    // Los tipos de datos están definidos en
    // la libreríapthread.
    pthread_t idHilo;
    pthread_attr_t atributos;
    int i;
    char valorDevuelto;
    // Inicializo el semáforo (mutex)
    pthread_mutex_init(&mutex, NULL);
    // Inicializo loe atributos del hilo.
    pthread_attr_init(&atributos);
    // Seteo el estado inicial del hilo.
    // PTHREAD_CREATE_JOINABLE --> indica que voy a esperar la finalización
    // del hilo. Esto me permite usar la funcion pthread_join() que esta
    // más abajo.
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);
    // pthread_create lanza el hilo. Le paso como parámetro:
    // idHilo ---> se carga cuando se crea el hilo.
    // atributos ---> los atributos del hilo.
    // funcionThread ---> es el nombre de la función que se va a ejecutar
    //  al crear el hilo.
    // NULL ---> iría la dirección de memoria que recibe como parámetro
    // la función del hilo (voidparametro).
    if (pthread_create(&idHilo, &atributos, funcionThread, NULL) != 0)
    {
        perror("No puedo crear thread");
        exit(-1);
    } // Mientras se ejecutan los hilos continua ejecutandose el main.
    for (i = 0; i < CANTIDAD_THREADS; i++)
    {
        pthread_mutex_lock(&mutex);
        printf("Soy el padre y tengo el mutex\n");
        sleep(1);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    printf("Padre : Espero al thread\n");
    // pthread_join es una funcion bloqueante que evita que
    // finalice el main(). Se desbloquea cuando van finalizando
    // los hilos. Le paso el idHilo que tiene que esperar.
    // Cada idHilo es unico para cada hilo.
    pthread_join(idHilo, (void **)&valorDevuelto);
    printf("Padre : Ya ha terminado el thread\n");
    printf("Padre : devuelve %c\n", valorDevuelto);
    return 0;
}
