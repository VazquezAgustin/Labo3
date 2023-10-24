#include <semaforo.h>
#include <global.h>
#include <definiciones.h>
#include <funcionesthreads.h>
#include <pthread.h>

int main(int arg, char *argv[])
{
    // hilos, semaforos, colas, etc
    pthread_t *idHilo;
    pthread_attr_t atributos;
    int i;
    char valorDevuelto;
    // generales
    int cantidad_jugadores = 0;
    int numero_aleatorio = 0;
    int alguien_acerto = 0;

    if (arg != 2) {
        printf("Uso: <Cantidad de jugadores> como parametro de entrada \n");
        return 1;
    }

    cantidad_jugadores = atoi(argv[1]);

    // genero nro al azar
    srand(time(NULL));
    numero_aleatorio = (rand() % 99) + 1;
    idHilo = (pthread_t* ) malloc(sizeof(pthread_t)*cantidad_jugadores);

    // hilos
    pthread_mutex_init(&mutex, NULL);
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    thread_data_info.numero_aleatorio = numero_aleatorio;
    thread_data_info.alguien_acerto = alguien_acerto;

    for (i = 0; i < cantidad_jugadores; i++)
    {
        if (pthread_create(&idHilo[i], &atributos, funcionThread, &thread_data_info) != 0) {
            perror("No puedo crear thread");
            exit(-1);
        } // Mientras se ejecutan los hilos continua ejecutandose el main.
    }
    printf("Padre : Espero al thread\n");
    pthread_join(*idHilo, (void **)&valorDevuelto);
    printf("Padre : Ya ha terminado el thread\n");
    printf("Padre : devuelve %c\n", valorDevuelto);

    free(idHilo);

    return 0;
}
