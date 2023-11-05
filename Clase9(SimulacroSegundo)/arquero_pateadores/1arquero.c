// arquero
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

int main(int arg, char *argv[])
{   
    // memoria y semaforo
    int id_cola_mensajes;
    mensaje msg;
    //comunes
    int numeroAleatorio = 0;
    int cantidad_tiros = 0;
    int array_jugadores_hicieron_gol[5];
    int index_printf = 0;
    int i = 0;

    // inicializaciones
    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    srand(time(NULL));
    borrar_mensajes(id_cola_mensajes);
    for (i = 0; i < 5; i++) {
        array_jugadores_hicieron_gol[i] = 0;
    }

    while (cantidad_tiros <= CANTIDAD_PATEADORES){
        printf("esperando tiro \n");
        recibir_mensaje(id_cola_mensajes, MSG_ARQUERO, &msg, 0);

        numeroAleatorio = (rand() % 4) + 2;
        usleep(500 * 1000);

        pthread_mutex_lock(&mutex);
            msg.int_evento = (rand() % 4) + 2; // evento del 2 al 5
            msg.long_dest = MSG_PATEADOR + cantidad_tiros;
            msg.int_rte = MSG_ARQUERO;
            enviar_mensaje(id_cola_mensajes, msg.long_dest, msg.int_rte, msg.int_evento);
            printf("\nArquero dice que fue evento nro %d", msg.int_evento);

            if(msg.int_evento == EVT_GOL){
                array_jugadores_hicieron_gol[cantidad_tiros] = msg.int_rte;
            }

            cantidad_tiros = cantidad_tiros + 1;
            printf("\n");
        pthread_mutex_unlock(&mutex);
    }

    printf("jugadores que convirtieron: \n");
    for (index_printf = 0; index_printf < CANTIDAD_PATEADORES; index_printf++) {
        if(array_jugadores_hicieron_gol[index_printf] != 0){
            printf("%d \n", array_jugadores_hicieron_gol[index_printf]);
        }   
    }
    printf("\n");

    return 0;
}
