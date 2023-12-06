// aca se definen las funciones que se van a ejecutar por los hilos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <global.h>
#include <unistd.h>
#include <colamensaje.h>
#include <semaforo.h>
#include <memoria.h>

void *funcionThreadEquipo1(void *threadarg){

    // memoria y semaforo
    int id_cola_mensajes;
    int idThread = 0;
    datosThread *datos_thread = (datosThread*) threadarg;
    //comunes

    printf("adentro hilo \n");
    // paso en limpio inputs
    idThread = datos_thread->idThread;
    id_cola_mensajes = datos_thread->id_cola_mensajes;

    pthread_mutex_lock(&mutex_proceso_1);
        printf("Jugador %d Equipo 1 Pateo \n", idThread);
        enviar_mensaje(id_cola_mensajes, MSG_EQUIPO2_ARQUERO, idThread, EVT_TIRO);
    pthread_mutex_unlock(&mutex_proceso_1);

    return 0;
}

void *funcionThreadArqueroEquipo1(void *threadarg){

    // memoria y semaforo
    int id_cola_mensajes;
    int idThread = 0;
    mensaje msg;
    datosThread *datos_thread = (datosThread*) threadarg;
    dato_marcador_array *marcador = NULL;
    int id_memoria_marcador;
    //comunes
    int numeroAleatorio = 0;
    int goles_a_sumar = 1;

    printf("adentro arquero 1\n");

    marcador = (dato_marcador_array*)creo_memoria(sizeof(dato_marcador_array), &id_memoria_marcador, CLAVE_BASE);

    // paso en limpio inputs
    idThread = datos_thread->idThread;
    id_cola_mensajes = datos_thread->id_cola_mensajes;

    srand(time(NULL));
    numeroAleatorio = rand() % 2;

    pthread_mutex_lock(&mutex_proceso_1);

        printf("Arquero equipo 1 Esperando tiro \n");
        recibir_mensaje(id_cola_mensajes, idThread, &msg, 0);
        if (msg.int_rte == MSG_EQUIPO2_ARQUERO)
        {
            goles_a_sumar = 2;
        }

        if(numeroAleatorio == 1){
            printf("Arquero %d Equipo 1 Dice fue gol", idThread);
            
            marcador->equipo[1].goles = marcador->equipo[1].goles + goles_a_sumar;
        }
        if(numeroAleatorio == 0){
            printf("Arquero %d Equipo 1 Dice fue afuera\n", idThread);
        }
    pthread_mutex_unlock(&mutex_proceso_1);

    return 0;
}

void *funcionThreadEquipo2(void *threadarg){

    // memoria y semaforo
    int id_cola_mensajes;
    int idThread = 0;
    datosThread *datos_thread = (datosThread*) threadarg;
    //comunes

    // paso en limpio inputs
    idThread = datos_thread->idThread;
    id_cola_mensajes = datos_thread->id_cola_mensajes;

    pthread_mutex_lock(&mutex_proceso_2);
        printf("Jugador %d Equipo 2 Pateo \n", idThread);
        enviar_mensaje(id_cola_mensajes, MSG_EQUIPO1_ARQUERO, idThread, EVT_TIRO);
    pthread_mutex_unlock(&mutex_proceso_2);

    return 0;
}

void *funcionThreadArqueroEquipo2(void *threadarg){

    // memoria y semaforo
    int id_cola_mensajes;
    int idThread = 0;
    mensaje msg;
    datosThread *datos_thread = (datosThread*) threadarg;
    dato_marcador_array *marcador = NULL;
    int id_memoria_marcador;
    //comunes
    int numeroAleatorio = 0;
    int goles_a_sumar = 1;

    marcador = (dato_marcador_array*)creo_memoria(sizeof(dato_marcador_array), &id_memoria_marcador, CLAVE_BASE);

    // paso en limpio inputs
    idThread = datos_thread->idThread;
    id_cola_mensajes = datos_thread->id_cola_mensajes;

    srand(time(NULL));
    numeroAleatorio = rand() % 2;

    pthread_mutex_lock(&mutex_proceso_2);

        printf("Arquero equipo 2 Esperando tiro \n");
        recibir_mensaje(id_cola_mensajes, idThread, &msg, 0);
        if (msg.int_rte == MSG_EQUIPO1_ARQUERO)
        {
            goles_a_sumar = 2;
        }

        if(numeroAleatorio == 1){
            printf("Arquero %d Equipo 2 Dice fue gol\n", idThread);
            
            marcador->equipo[0].goles = marcador->equipo[0].goles + goles_a_sumar;
        }
        if(numeroAleatorio == 0){
            printf("Arquero %d Equipo 2 Dice fue afuera\n", idThread);
        }
    pthread_mutex_unlock(&mutex_proceso_2);

    return 0;
}
