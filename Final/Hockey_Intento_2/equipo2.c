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
    int id_cola_mensajes = 0;
    pthread_t *idThread = NULL;
    pthread_attr_t atributos;
    datosThread *datos_thread = NULL;
    //comunes
    int id_semaforo = 0;
    int id_memoria_marcador = 0;
    int index_creacion_threads = 0;
    dato_marcador_array *marcador = NULL;
    int numeroAleatorio = 0;
    int continuar = 1;

    marcador = (dato_marcador_array*)creo_memoria(sizeof(dato_marcador_array), &id_memoria_marcador, CLAVE_BASE);
    idThread = (pthread_t *)malloc(sizeof(pthread_t)*CANTIDAD_JUGADORES);
    datos_thread = (datosThread *)malloc(sizeof(datosThread)* CANTIDAD_JUGADORES);
    srand(time(NULL));

    // El programa no comienza hasta que el ultimo equipo sea inicializado en el marcador
    while (strcmp(marcador->equipo[CANTIDAD_EQUIPOS - 1].nombre, "") == 0)
    {
        printf("esperando primer proceso... \n");
        sleep(1);
    }

    for (index_creacion_threads=0; index_creacion_threads<CANTIDAD_JUGADORES; index_creacion_threads++){
        datos_thread[index_creacion_threads].idThread = MSG_EQUIPO2_ARQUERO + index_creacion_threads;
        datos_thread[index_creacion_threads].id_cola_mensajes = id_cola_mensajes;
        datos_thread[index_creacion_threads].output_evento = 0;
    }

    pthread_create(&idThread[0], &atributos, funcionThreadArqueroEquipo2, &datos_thread[0]);
    pthread_join (idThread[0], NULL);

    while (continuar == 1)
    {
        espera_semaforo(id_semaforo);
            numeroAleatorio = (rand() % 5) + 1;
            pthread_create(&idThread[numeroAleatorio], &atributos, funcionThreadEquipo2, &datos_thread[numeroAleatorio]); 
            pthread_join (idThread[numeroAleatorio], NULL);
            usleep(600 * 1000);
        levanta_semaforo(id_semaforo);
    }

    free(idThread);

    return 0;
}
