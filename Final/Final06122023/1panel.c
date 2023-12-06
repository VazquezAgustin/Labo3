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

void procesar_evento(mensaje msg, eventos array_eventos_ocurridos[],dato_inicio *memoria_inicio_lluvia)
{
    // dejado en caso de necesitar debug
    // printf("Destino %d\n", (int)msg.long_dest);
    // printf("Remitente %d\n", msg.int_rte);
    // printf("Evento %d\n", msg.int_evento);
    switch (msg.int_evento)
    {
    case EVT_INFO:

        switch (msg.int_rte)
        {
        case MSG_RAYOS:
            printf("Rayos detectados \n");
            array_eventos_ocurridos[0].cantidad_detectados ++;
            break;
        
        case MSG_TRUENOS:
            printf("Truenos detectados \n");
            array_eventos_ocurridos[1].cantidad_detectados ++;
            if (memoria_inicio_lluvia->iniciar == 0)
            {
                memoria_inicio_lluvia->iniciar = 1;
            }
            break;

        case MSG_RELAMPAGOS:
            printf("Relampagos detectados \n");
            array_eventos_ocurridos[2].cantidad_detectados ++;
            break;
        
        case MSG_LLUVIA:
            printf("Llueve \n");
            break;
        
        default:
            printf("\nActividad anormal detectada en la tormenta\n");
            break;
        }
        break;
        
    default:
        printf("\nEvento sin definir\n");
        break;
    }
}

int main(int arg, char *argv[])
{   
    int id_cola_mensajes;
    mensaje msg;
    //comunes
    eventos array_eventos_ocurridos[3];
    int id_memoria_inicio = 0;
    int id_memoria_inicio_lluvia = 0;
    dato_inicio *memoria_inicio = NULL;
    dato_inicio *memoria_inicio_lluvia = NULL;
    int index_contador = 0;

    // inicializaciones
    memoria_inicio = (dato_inicio*)creo_memoria(sizeof(dato_inicio), &id_memoria_inicio, CLAVE_BASE);
    memoria_inicio_lluvia = (dato_inicio*)creo_memoria(sizeof(dato_inicio), &id_memoria_inicio_lluvia, CLAVE_BASE + 1000);
    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE + 400);
    borrar_mensajes(id_cola_mensajes);

    // flag de sincronismo
    memoria_inicio->iniciar = 0;

    // flag inicio lluvia
    memoria_inicio_lluvia->iniciar = 0;

    //inicializacion de contador de rayos,relampagos,truenos
    printf("Inicializando contador: \n");
    // rayos
    memset(array_eventos_ocurridos[0].nombre_evento, 0x00, sizeof(array_eventos_ocurridos[0].nombre_evento));
    strcpy(array_eventos_ocurridos[0].nombre_evento, "rayos");
    array_eventos_ocurridos[0].cantidad_detectados = 0;
    // relampagos
    memset(array_eventos_ocurridos[1].nombre_evento, 0x00, sizeof(array_eventos_ocurridos[1].nombre_evento));
    strcpy(array_eventos_ocurridos[1].nombre_evento, "relampagos");
    array_eventos_ocurridos[1].cantidad_detectados = 0;
    // truenos
    memset(array_eventos_ocurridos[2].nombre_evento, 0x00, sizeof(array_eventos_ocurridos[2].nombre_evento));
    strcpy(array_eventos_ocurridos[2].nombre_evento, "truenos");
    array_eventos_ocurridos[2].cantidad_detectados = 0;

    for (index_contador = 0; index_contador < 3; index_contador++)
    {
        printf("Evento %s cantidad %d \n", array_eventos_ocurridos[index_contador].nombre_evento, array_eventos_ocurridos[index_contador].cantidad_detectados);
    }
    
    memoria_inicio->iniciar = 1;

    printf("------- \n");

    while (memoria_inicio->iniciar == 1)
    {
        recibir_mensaje(id_cola_mensajes, MSG_PANEL, &msg, 0);

        procesar_evento(msg, array_eventos_ocurridos, memoria_inicio_lluvia);
        
        for (index_contador = 0; index_contador < 3; index_contador++)
        {
            printf("Evento %s cantidad %d \n", array_eventos_ocurridos[index_contador].nombre_evento, array_eventos_ocurridos[index_contador].cantidad_detectados);
        }
        printf("--------------\n");
    }
    
    shmdt ((char *)memoria_inicio);
	shmctl (id_memoria_inicio, IPC_RMID, (struct shmid_ds *)NULL);
    shmdt ((char *)id_memoria_inicio_lluvia);
	shmctl (id_memoria_inicio_lluvia, IPC_RMID, (struct shmid_ds *)NULL);

    return 0;
}
