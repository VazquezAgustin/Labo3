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
    dato_marcador_array *marcador = NULL;
    int id_semaforo = 0;
    //comunes
    int id_memoria_marcador = 0;
    int index_marcador = 0;
    char equipo_nombre[50];
    int index_creacion_threads = 0;
    int numeroAleatorio = 0;
    int continuar = 1;

    // Inicializando
    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);

    marcador = (dato_marcador_array*)creo_memoria(sizeof(dato_marcador_array), &id_memoria_marcador, CLAVE_BASE);
    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE + 40);
    srand(time(NULL));
    borrar_mensajes(id_cola_mensajes);
    idThread = (pthread_t *)malloc(sizeof(pthread_t)*CANTIDAD_JUGADORES);
    datos_thread = (datosThread *)malloc(sizeof(datosThread)* CANTIDAD_JUGADORES);

    printf("Llenando marcador\n");
    for (index_marcador = 0; index_marcador < CANTIDAD_EQUIPOS; index_marcador++)
    {
        // nombre
        memset(marcador->equipo[index_marcador].nombre, 0x00, sizeof(marcador->equipo[index_marcador].nombre));
        snprintf(equipo_nombre, sizeof(equipo_nombre), "equipo%d", index_marcador + 1);
        strcpy(marcador->equipo[index_marcador].nombre, equipo_nombre);
        // goles
        marcador->equipo[index_marcador].goles = 0;
    }

    for (index_marcador = 0; index_marcador < CANTIDAD_EQUIPOS; index_marcador++)
    {
        printf("Nombre %s - %d \n", marcador->equipo[index_marcador].nombre, marcador->equipo[index_marcador].goles);
    }
    // LOGICA
    
    for (index_creacion_threads=0; index_creacion_threads<CANTIDAD_JUGADORES; index_creacion_threads++)
    {
        datos_thread[index_creacion_threads].idThread = MSG_EQUIPO1_ARQUERO + index_creacion_threads;
        datos_thread[index_creacion_threads].id_cola_mensajes = id_cola_mensajes;
        datos_thread[index_creacion_threads].output_evento = 0;
    }
    
    while (continuar == 1)
    {
        espera_semaforo(id_semaforo);
            numeroAleatorio = rand() % 5;
            pthread_create(&idThread[numeroAleatorio], &atributos, funcionThreadEquipo1, &datos_thread[numeroAleatorio]); 
            pthread_join (idThread[numeroAleatorio], NULL);
            usleep(600 * 1000);
        levanta_semaforo(id_semaforo);

        // espera_semaforo(id_semaforo);
            if (marcador->equipo[0].goles < 5 && marcador->equipo[1].goles < 5)
            {
                printf("Equipo 1 - %d goles \n", marcador->equipo[0].goles);
                printf("Equipo 2 - %d goles \n", marcador->equipo[1].goles);
                printf("--------------------- \n");

                pthread_create(&idThread[0], &atributos, funcionThreadArqueroEquipo1, &datos_thread[0]);
                sleep(10);
                pthread_join (idThread[0], NULL);
            }
            else
            {
                continuar = 0;
            }
        // levanta_semaforo(id_semaforo);
    }

    free(idThread);
    shmdt ((char *)marcador);
	shmctl (id_memoria_marcador, IPC_RMID, (struct shmid_ds *)NULL);
    msgctl (id_cola_mensajes, IPC_RMID, NULL);

    return 0;
}
