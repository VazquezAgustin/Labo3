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
#define CANTIDAD_MAXIMA_EVENTOS 100
#define CANTIDAD_THREADS 4
#define CANTIDAD_EVENTOS_POR_THREADS 25

// Variables de ejercicio
typedef struct struct_eventos eventos;
struct struct_eventos
{
    char nombre_evento[20];
    int cantidad_detectados;
};

// Variables de cola de mensaje
typedef struct tipo_mensajes mensaje;
struct tipo_mensajes
{
    long long_dest;                    // Destinatario
    int int_rte;                       // Remitente
    int int_evento;                    // Numero de evento
    int cantidad;
};

typedef struct tipo_datosThread{
    int idThread;
    int id_cola_mensajes;
}datosThread;

struct tipo_datos
{
    int dato;
};

typedef enum
{
    MSG_NADIE,    //0
    MSG_PANEL,  //1
    MSG_RAYOS, // 2
    MSG_TRUENOS, // 3
    MSG_RELAMPAGOS, // 4
    MSG_LLUVIA // 5
} Destinos;

typedef enum{
    EVT_NINGUNO, //0 
    EVT_INFO, //1
    EVT_FIN //2
} Eventos;

typedef struct Flag dato_inicio;
struct Flag{
    int iniciar;
};

// Variable global para semaforo(Mutex)
pthread_mutex_t mutex_proceso_1;
pthread_mutex_t mutex_proceso_2;

#endif
