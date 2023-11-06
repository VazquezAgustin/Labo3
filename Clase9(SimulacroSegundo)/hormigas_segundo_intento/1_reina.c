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
    pthread_t* idHilo;
    pthread_attr_t atributos;
    int id_cola_mensajes;
    mensaje msg;
    int id_memoria;
    //comunes
    int cantidad_hormigas = 0;
    int index_inicializar_cantidad = 0;

    // input usuario
    if (arg == 2){
        cantidad_hormigas = atoi(argv[1]);
    }else{
        printf("Uso: enviar <int> junto al ejecutable para definir cantidad de hormigas.\n");
        return 1;
    }

    memoria = (dato*)creo_memoria(sizeof(cliente)*CANTIDAD, &id_memoria, CLAVE_BASE);

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

    return 0;
}
