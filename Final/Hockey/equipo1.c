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
    int id_memoria_moneda = 0;
    int id_memoria_marcador = 0;
    int id_cola_mensajes = 0;
    dato_moneda *memoria_moneda = NULL;
    dato_marcador *memoria_marcador = NULL;
    pthread_t *idThread = NULL;
    pthread_attr_t atributos;
    datosThread *datos_thread = NULL;
    //comunes
    int index_creacion_threads = 0;
    int numeroRandom = 0;
    int numero_equipo = 0;
    int inicio_jugadores = 0;

    // inicializaciones
    memoria_moneda = (dato_moneda*)creo_memoria(sizeof(dato_moneda), &id_memoria_moneda, CLAVE_BASE + 40);
    memoria_moneda->comienza_equipo = 0;
    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    srand(time(NULL));
    borrar_mensajes(id_cola_mensajes);
    memoria_marcador = (dato_marcador*)creo_memoria(sizeof(dato_marcador) * CANTIDAD_EQUIPOS, &id_memoria_marcador, CLAVE_BASE + 100);
    
    if (arg == 2){
        numero_equipo = atoi(argv[1]);
    }
    else
    {
        printf("Uso: Ingrese el numero de equipo que sera el proceso lanzado (1 o 2)\n");
        exit(-1);
    }

    // Genera un número aleatorio entre 1 y 2
    numeroRandom = rand() % 2 + 1;
    memoria_moneda->comienza_equipo = numeroRandom;

    // Inicializo marcador
    memset(memoria_marcador[0].nombre, 0x00, sizeof(memoria_marcador[0].nombre));
    strcpy(memoria_marcador[0].nombre, "EQUIPO1");
    memoria_marcador[0].goles = 0;
    memset(memoria_marcador[1].nombre, 0x00, sizeof(memoria_marcador[1].nombre));
    strcpy(memoria_marcador[1].nombre, "EQUIPO2");
    memoria_marcador[1].goles = 0;

    // logica
    printf("------- \n");
    sleep(1);

    // creo threads
    if (numero_equipo == 1)
    {
        inicio_jugadores = 1;
    }
    if (numero_equipo == 2)
    {
        inicio_jugadores = 6;
    }

    datos_thread = (datosThread *)malloc(sizeof(datosThread)*CANTIDAD_JUGADORES);
    
    while (memoria_marcador[0]->goles <= 5 && memoria_marcador[1]->goles <= 5)
    {
        for (index_creacion_threads=inicio_jugadores; index_creacion_threads<inicio_jugadores + CANTIDAD_JUGADORES; index_creacion_threads++){
            datos_thread[index_creacion_threads].idThread = index_creacion_threads;
            datos_thread[index_creacion_threads].id_cola_mensajes = id_cola_mensajes;
            datos_thread[index_creacion_threads].output_evento = 0;
            datos_thread[index_creacion_threads].nro_equipo = numero_equipo;
            printf("idJugador: %d\tid_cola_mensajes: %d \n", datos_thread[index_creacion_threads].idThread, datos_thread[index_creacion_threads].id_cola_mensajes);
            pthread_create(&idThread[index_creacion_threads], &atributos, funcionThread, &datos_thread[index_creacion_threads]);

            pthread_join (idThread[index_creacion_threads], NULL);
        }
    }
    
    }

    // cleanup
    free(idThread);
    borrar_mensajes(id_cola_mensajes);
    msgctl (id_cola_mensajes, IPC_RMID, NULL);

    shmdt ((char *)memoria_marcador);
	shmctl (id_memoria_marcador, IPC_RMID, (struct shmid_ds *)NULL);

    shmdt ((char *)memoria_moneda);
	shmctl (id_memoria_moneda, IPC_RMID, (struct shmid_ds *)NULL);

    return 0;
}
