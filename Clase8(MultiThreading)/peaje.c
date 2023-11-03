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
#include <pthread.h>

int main(int arg, char *argv[])
{   
    // memoria, semaforo, colas, hilos
    pthread_t *idHilo;
    pthread_attr_t atributos;
    int id_memoria;
    dato *memoria = NULL;
    int id_semaforo;
    FILE *archivo = NULL;
    //comunes
    //struct Via vias[CANTIDAD_VIAS] = {{0}, {0}, {0}}; // Inicialización estática
    int duracion_aleatoria;
    int contador_for;
    int valor_actual;
    int via;
    int contador_mas_10 = 0;

    // Inicializaciones
    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);
    memoria = (dato*)creo_memoria(sizeof(dato)*CANTIDAD, &id_memoria, CLAVE_BASE);
    srand(time(NULL));
    duracion_aleatoria = rand()%(100-5000);

    // hilos
    pthread_mutex_init(&mutex, NULL);
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    thread_data_info.numero_aleatorio = numero_aleatorio;
    thread_data_info.alguien_acerto = alguien_acerto;

    

    //Inicializar estructura
    for (via = 0; via < CANTIDAD_VIAS; via++)
    {
        memoria[via].vehiculos_en_cola = 0;
    }



    shmdt ((char *)memoria);
	shmctl (id_memoria, IPC_RMID, (struct shmid_ds *)NULL);

    return 0;
}
