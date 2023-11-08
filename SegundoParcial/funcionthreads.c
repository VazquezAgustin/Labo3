// aca se definen las funciones que se van a ejecutar por los hilos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <global.h>
#include <unistd.h>
#include <colamensaje.h>

void *funcionThread(void *threadarg){

    // memoria y semaforo
    int id_cola_mensajes;
    int idThread = 0;
    mensaje msg;
    datosThread *datos_thread = (datosThread*) threadarg;
    //comunes
    int mensaje_recibido = 0;
    int inicio = 0;
    int cantidad_vueltas = 0;
    int voto;
    int index_vueltas = 0;

    // paso en limpio inputs
    idThread = datos_thread->idThread;
    id_cola_mensajes = datos_thread->id_cola_mensajes;

    srand(time(NULL));
    cantidad_vueltas = 100 / CANTIDAD_VOTANTES;

    // espero a que inicien las votaciones
    while (inicio == 0)
    {
        mensaje_recibido = recibir_mensaje(id_cola_mensajes, idThread, &msg, 1);
        if (mensaje_recibido > 0){
            inicio = 1;
        }
    }

    // podria hacer la votacion de preisdente y vice con un loop por fuera del for para evitar reescribir codigo pero prefiero hacerlo asi para darle visibilidad a la consigna
    for (index_vueltas = 0; index_vueltas < cantidad_vueltas; index_vueltas++)
    {
        pthread_mutex_lock(&mutex);
            voto = rand() % 2;
            printf("Votante %d votando presidente %d \n", idThread, voto);
            usleep(200 * 1000);
            enviar_mensaje(id_cola_mensajes, MSG_PANEL, idThread, EV_PRESIDENTE, voto);
        pthread_mutex_unlock(&mutex);
    }

    for (index_vueltas = 0; index_vueltas < cantidad_vueltas; index_vueltas++)
    {
        pthread_mutex_lock(&mutex);
            voto = rand() % 2;
            printf("Votante %d votando presidente %d \n", idThread, voto);
            usleep(200 * 1000);
            enviar_mensaje(id_cola_mensajes, MSG_PANEL, idThread, EV_VICE, voto);
        pthread_mutex_unlock(&mutex);
        usleep(300 * 1000);
    }

    printf("Thread %d termino \n", idThread);

    return 0;
}
