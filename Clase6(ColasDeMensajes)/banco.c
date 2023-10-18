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

void procesar_evento(int id_cola_mensajes, mensaje msg)
{
    // memoria, semaforos
    int id_memoria;	
	dato *memoria = NULL;
    // otras
	char cadena[100];
	static int cantidad=0;  //es inicializada solo una vez, mantiene el valor en las sucesivas llamadas.
	printf("Destino   %d\n", (int) msg.long_dest);
	printf("Remitente %d\n", msg.int_rte);
	printf("Evento    %d\n", msg.int_evento);
	printf("Mensaje   %s\n", msg.char_mensaje);

    memoria = (dato*)creo_memoria(sizeof(dato)*CANTIDAD, &id_memoria, CLAVE_BASE);

	switch (msg.int_evento)
	{
		case EVT_CONSULTA_SALDO:
			printf("Consulta saldo\n");

            

			enviar_mensaje(id_cola_mensajes , msg.int_rte, MSG_BANCO, EVT_RTA_SALDO, cadena);
		break;

		case EVT_DEPOSITO:
			break;
		
        case EVT_EXTRACCION:
            break;

		break;
	}
	printf("------------------------------\n");
}

int main(int arg, char *argv[])
{   
    int id_cola_mensajes;
    mensaje msg;

    recibir_mensaje(id_cola_mensajes, MSG_BANCO, &msg);

    return 0;
}
