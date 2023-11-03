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
#include <funcionthreads.h>
#include <colamensaje.h>

void procesar_evento(int id_cola_mensajes, mensaje msg, insumos insumo[])
{
    printf("Destino %d\n", (int)msg.long_dest);
    printf("Remitente %d\n", msg.int_rte);
    printf("Evento %d\n", msg.int_evento);
    printf("Mensaje %d\n", msg.cantidad_insumo);
    switch (msg.int_evento)
    {
    case EVT_GUARDAR_MADERA:
        printf("EVT_GUARDAR_MADERA\n");
        
        insumo[0].cant_de_insumo = insumo[0].cant_de_insumo + msg.cantidad_insumo;
        printf("Cantidad de madera = %d\n", insumo[0].cant_de_insumo);
        if(insumo[0].cant_de_insumo >= 90){
        }else{
            enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_HORMIGA_REINA, 1, 0);
        }
        break;
    case EVT_GUARDAR_HOJAS:
        printf("EVT_GUARDAR_HOJAS\n");
        
        insumo[1].cant_de_insumo = insumo[1].cant_de_insumo + msg.cantidad_insumo;
        printf("Cantidad de hojas = %d\n", insumo[1].cant_de_insumo);
        if(insumo[1].cant_de_insumo >= 90){
        }else
        {
            enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_HORMIGA_REINA, 2, 0);
        }
        break;
    case EVT_GUARDAR_COMIDA:
        printf("EVT_GUARDAR_COMIDA\n");
        
        insumo[2].cant_de_insumo = insumo[2].cant_de_insumo + msg.cantidad_insumo;
        printf("Cantidad de comida = %d\n", insumo[2].cant_de_insumo);
        if(insumo[2].cant_de_insumo >= 90){
        }else
        {
            enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_HORMIGA_REINA, 3, 0);
        }
        break;
    case EVT_GUARDAR_SEMILLA:
        printf("EVT_GUARDAR_SEMILLA\n");
        
        insumo[3].cant_de_insumo = insumo[3].cant_de_insumo + msg.cantidad_insumo;
        printf("Cantidad de semillas = %d\n", insumo[3].cant_de_insumo);
        if(insumo[3].cant_de_insumo >= 90){
        }else
        {
            enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_HORMIGA_REINA, 4, 0);
        }
        break;
    default:
        printf("\nEvento sin definir\n");
        break;
    }
    printf("------------------------------\n");
}

int main(int arg, char *argv[])
{   
    // memoria y semaforo
    pthread_t* idHilo;
    pthread_attr_t atributos;
    int id_cola_mensajes;
    mensaje msg;
    //comunes
    insumos insumo[4];
    int cantidad_hormigas = 0;
    int terminado = 0;
    int index_inicializar_cantidad = 0;
    int index_crear_threads = 0;
    int hormiga_actual = 2;

    // input usuario
    if (arg == 2){
        cantidad_hormigas = atoi(argv[1]);
    }else{
        printf("Uso: enviar <int> junto al ejecutable para definir cantidad de hormigas. MAX 3 HORMIGAS \n\n");
        return 1;
    }

    // definir 4 tipo de insumos
    strcpy(insumo[0].tipo_insumo, "Madera");
    strcpy(insumo[1].tipo_insumo, "Hojas");
    strcpy(insumo[2].tipo_insumo, "Comida");
    strcpy(insumo[3].tipo_insumo, "Semillas");

    // inicializar cantidad de insumo en 0
    for (index_inicializar_cantidad = 0; index_inicializar_cantidad < 4; index_inicializar_cantidad++)
    {
        insumo[index_inicializar_cantidad].cant_de_insumo = 0;
    }

    // Preparo el terreno para los threads
    idHilo = (pthread_t* ) malloc(sizeof(pthread_t)*cantidad_hormigas);
    pthread_mutex_init(&mutex, NULL);
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    // Preparo la cola de mensaje
    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

    // Crear N cantidad de threadhormiga
    for (index_crear_threads = 0; index_crear_threads < cantidad_hormigas; index_crear_threads++)
    {
        thread_data_info.id_cola_mensajes = id_cola_mensajes;
        thread_data_info.nro_hormiga = index_crear_threads;
        if (pthread_create(&idHilo[index_crear_threads], &atributos, funcionThread, &thread_data_info) != 0)
        {
            perror("No puedo crear thread");
            exit(-1);
        }
        sleep(1);
    }

    // Recibir por teclado tipo de insumo a recolectar 
    while (terminado == 0)
    {
        for (hormiga_actual = 0; hormiga_actual < cantidad_hormigas; hormiga_actual++)
        {
            enviar_mensaje(id_cola_mensajes, hormiga_actual + 2, MSG_HORMIGA_REINA, insumo_teclado , 0);
        }

        if(insumo[0].cant_de_insumo >= 90){

        }else{
            enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_HORMIGA_REINA, 1, 0);
        }

        recibir_mensaje(id_cola_mensajes, MSG_HORMIGA_REINA, &msg);
        procesar_evento(id_cola_mensajes, msg, insumo, terminado);
        sleep(5);
    }
    
    for(index_crear_threads=0; index_crear_threads<cantidad_hormigas; index_crear_threads++)
	{
		pthread_join (idHilo[index_crear_threads], NULL);
		printf("TERMINO\n");
	}	
    
    return 0;
}
