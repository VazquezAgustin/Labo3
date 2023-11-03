// aca se definen las funciones que se van a ejecutar por los hilos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <global.h>
#include <unistd.h>
#include <colamensaje.h>

void *funcionThread(void *parametro){

    // cola msg, etc.
    mensaje msg;
    // comunes
    int cantidad_recolectada = 0;
    // recibo estructura con nro_hormiga y id_cola_msg
    struct thread_data *my_data;
    my_data = (struct thread_data *) parametro;

    srand(time(NULL));

    while(1)
    {
        recibir_mensaje(my_data->id_cola_mensajes, my_data->nro_hormiga, &msg);
        cantidad_recolectada = 0;
        printf("Hormiga %d recolectando insumo %d cantidad %d \n", my_data->nro_hormiga, msg.int_evento, cantidad_recolectada);
        cantidad_recolectada = (rand() % 4) + 1;
        enviar_mensaje(my_data->id_cola_mensajes, MSG_HORMIGA_REINA, my_data->nro_hormiga, msg.int_evento + 4, cantidad_recolectada);
        
        usleep(300000);
        
    }
    return 0;
}
