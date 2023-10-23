#include <semaforo.h>
#include <global.h>
#include <colamensaje.h>
#include <definiciones.h>
#include <funcionesthreads.h>
#include <pthread.h>


int main(int arg, char *argv[])
{
    // hilos, semaforos, colas, etc
    pthread_t idHilo;
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

    // hilos
    pthread_mutex_init(&mutex, NULL);
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    thread_data_info.numero_aleatorio = numero_aleatorio;
    thread_data_info.alguien_acerto = alguien_acerto;
    thread_data_info.cantidad_threads = cantidad_jugadores;

    if (pthread_create(&idHilo, &atributos, funcionThread, &thread_data_info) != 0) {
        perror("No puedo crear thread");
        exit(-1);
    } // Mientras se ejecutan los hilos continua ejecutandose el main.

    for (i = 0; i < cantidad_jugadores; i++)
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
