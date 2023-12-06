#ifndef _GLOBAL
#define _GLOBAL
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <time.h>
#include <string.h>
#include <pthread.h> 

#define LARGO_TMENSAJE 1024
#define CANTIDAD_EQUIPOS 2
#define CANTIDAD_JUGADORES 5

// Variables memoria compartida
typedef struct Marcador {
    char nombre[50];
    int goles;
} dato_marcador;

typedef struct MarcadorArray {
    dato_marcador equipo[CANTIDAD_EQUIPOS];
} dato_marcador_array;

// Variables de cola de mensaje
typedef struct tipo_mensajes mensaje;
struct tipo_mensajes
{
    long long_dest;                    // Destinatario
    int int_rte;                       // Remitente
    int int_evento;                    // Numero de evento
};

typedef struct tipo_datosThread{
    int idThread;
    int id_cola_mensajes;
    int output_evento;
}datosThread;

struct tipo_datos
{
    int dato;
};

typedef enum
{
    MSG_NADIE, //0
    MSG_EQUIPO1_ARQUERO = 1, // 1
    MSG_EQUIPO1_JUGADOR, // 2 
    MSG_EQUIPO2_ARQUERO = 6, // 6
    MSG_EQUIPO2_JUGADOR // 7
} Destinos;

typedef enum{
    EVT_NINGUNO, //0
    EVT_TIRO //1
} Eventos;

// Variable global para semaforo(Mutex)
pthread_mutex_t mutex_proceso_1;
pthread_mutex_t mutex_proceso_2;

#endif
