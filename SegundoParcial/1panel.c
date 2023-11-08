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
    int id_memoria;
    dato_flag *memoria = NULL;
    int id_cola_mensajes;
    mensaje msg;
    //comunes
    votos array_votos_presidenciales[2];
    votos array_votos_vice[2];
    int index_iniciar_threads = 0;
    int i = 0;
    int index_inicializar_cantidad = 0;

    // inicializaciones
    memoria = (dato_flag*)creo_memoria(sizeof(dato_flag), &id_memoria, CLAVE_BASE);
    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    srand(time(NULL));
    borrar_mensajes(id_cola_mensajes);
    pthread_mutex_init(&mutex, NULL);

    memoria->terminar = 0;

    strcpy(array_votos_presidenciales[0].nombre, "MS"); //PRESIDENTE
    strcpy(array_votos_presidenciales[1].nombre, "MI"); //PRESIDENTE

    strcpy(array_votos_vice[0].nombre, "A"); //VICE
    strcpy(array_votos_vice[1].nombre, "V"); //VICE

    for (index_inicializar_cantidad = 0; index_inicializar_cantidad < 2; index_inicializar_cantidad++)
    {
        array_votos_presidenciales[index_inicializar_cantidad].cantidad_votos = 0;
        array_votos_vice[index_inicializar_cantidad].cantidad_votos = 0;
    }

    // logica
    printf("------- \n");
    sleep(1);

    for (index_iniciar_threads = 0; index_iniciar_threads < CANTIDAD_VOTANTES; index_iniciar_threads++)
    {
        pthread_mutex_lock(&mutex);
            usleep(500 * 1000);
            msg.int_evento = EV_INIT;
            msg.long_dest = MSG_VOTANTE + index_iniciar_threads;
            msg.int_rte = MSG_PANEL;
            msg.voto_a_candidato = 0;
            enviar_mensaje(id_cola_mensajes, msg.long_dest, msg.int_rte, msg.int_evento, msg.voto_a_candidato);
            printf("Mensaje inicio votaciones thread %d enviado\n", index_iniciar_threads);
        pthread_mutex_unlock(&mutex);
    }

    while (memoria->terminar == 0)
    {
        recibir_mensaje(id_cola_mensajes, MSG_PANEL, &msg, 0);

        switch (msg.int_evento)
        {
        case EV_PRESIDENTE:
            array_votos_presidenciales[msg.voto_a_candidato].cantidad_votos = array_votos_presidenciales[msg.voto_a_candidato].cantidad_votos + 1;
            
            printf("Votos presidenciales al momento:\n");
            for (i = 0; i < 2; i++)
            {
                printf("%s - %d \n", array_votos_presidenciales[i].nombre, array_votos_presidenciales[i].cantidad_votos);
            }
            break;
        
        case EV_VICE:
            array_votos_vice[msg.voto_a_candidato].cantidad_votos = array_votos_vice[msg.voto_a_candidato].cantidad_votos + 1;
            printf("Votos vice presidentes al momento:\n");
            for (i = 0; i < 2; i++)
            {
                printf("%s - %d \n", array_votos_vice[i].nombre, array_votos_vice[i].cantidad_votos);
            }
            break;

        default:
            printf("ERROR: evento no definido");
            break;
        }
    }

    shmdt ((char *)memoria);
	shmctl (id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
    
    return 0;
}
