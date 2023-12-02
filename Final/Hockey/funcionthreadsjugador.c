// aca se definen las funciones que se van a ejecutar por los hilos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <global.h>
#include <unistd.h>
#include <colamensaje.h>

void *funcionThreadJugador(void *threadarg){

    // memoria y semaforo
    int id_cola_mensajes;
    int idThread = 0;
    int nro_equipo = 0
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
    nro_equipo = datos_thread->nro_equipo;
    int id_memoria_moneda = 0;
    int id_memoria_marcador = 0;
    int id_arquero_equipo_opuesto = 0;
    dato_moneda *memoria_moneda = NULL;
    dato_marcador *memoria_marcador = NULL;

    memoria_moneda   = (dato_moneda*)creo_memoria(sizeof(dato_moneda), &id_memoria_moneda, CLAVE_BASE + 40);
    memoria_marcador = (dato_marcador*)creo_memoria(sizeof(dato_marcador) * CANTIDAD_EQUIPOS, &id_memoria_marcador, CLAVE_BASE + 100);

    // mutex a usar depende del nro de equipo al cual pertenece
    if (nro_equipo == 1)
    {
        id_arquero_equipo_opuesto = MSG_EQUIPO2_JUGADOR;
        pthread_mutex_lock(&mutex_proceso_1);
    }
    if (nro_equipo == 2)
    {
        id_arquero_equipo_opuesto = MSG_EQUIPO1_JUGADOR;
        pthread_mutex_lock(&mutex_proceso_2);
    }
    
    // verifico quien arranca y empiezo
    if (memoria_moneda->comienza_equipo == nro_equipo)
    {
        printf("Jugador %d - equipo %d - pateando \n", idThread, nro_equipo);
        // envio mensaje al arquero
        enviar_mensaje(id_cola_mensajes, id_arquero_equipo_opuesto, idThread, EVT_TIRO);
        memoria_moneda->comienza_equipo = 40;//desasigno porque ya arranco
    }else
    {
        while (memoria_marcador[0]->goles <= 5 && memoria_marcador[1]->goles <= 5)
        {   
            if (idThread == 0)
            {
                mensaje_recibido = recibir_mensaje(id_cola_mensajes, idThread, &msg, 1);
                if (mensaje_recibido > 0){
                    inicio = 1;
                }
            }
            
                
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
        usleep(600 * 1000);
    }

    for (index_vueltas = 0; index_vueltas < cantidad_vueltas; index_vueltas++)
    {
        pthread_mutex_lock(&mutex);
            voto = rand() % 2;
            printf("Votante %d votando vicepresidente %d \n", idThread, voto);
            enviar_mensaje(id_cola_mensajes, MSG_PANEL, idThread, EV_VICE, voto);
        pthread_mutex_unlock(&mutex);
        usleep(600 * 1000);
    }

    printf("Thread %d termino \n", idThread);

    return 0;
}
