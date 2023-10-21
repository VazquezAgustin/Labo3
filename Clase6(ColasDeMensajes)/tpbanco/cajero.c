#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include "memoria.h"
#include "semaforo.h"
#include <time.h>
#include "gestionarch.h"
#include "global.h"
#include "colamensaje.h"
#include <string.h>

int main(int arg, char *argv[])
{
    //memoria, semaforos y mensajes
	int id_memoria;	
	int id_semaforo;
    dato *memoria = NULL;
    int id_cola_mensajes;
	mensaje msg;
    //generales
    int menu_deseado = 0;
    char nro_cliente[4];
    char input_mensaje[20];

    id_semaforo = creo_semaforo();
    srand(time(NULL));
    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    
    printf("Ingrese menu deseado (1 para consultar saldo / 2 depositos / 3 para extracciones) \n");
    scanf("%d", &menu_deseado);

    switch (menu_deseado)
    {
    case 1:
        printf("Ingrese numero de cliente \n");
        scanf("%c", &nro_cliente);

        // nrocliente, saldo
        strcpy(input_mensaje, strcat(nro_cliente, ",0"));
        
        enviar_mensaje(id_cola_mensajes , MSG_BANCO, MSG_CAJERO_01, EVT_CONSULTA_SALDO, input_mensaje);
        
        break;
    
    case 2:
        break;
    case 3:
        break;
    default:
        break;
    }

    return 0;
}
