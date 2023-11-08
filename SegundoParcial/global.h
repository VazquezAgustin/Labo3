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
#define CANTIDAD_VOTANTES 2

// Variables de ejercicio
typedef struct struct_votos votos;
struct struct_votos
{
    char nombre[20];
    int cantidad_votos;
};

// Variables de cola de mensaje
typedef struct tipo_mensajes mensaje;
struct tipo_mensajes
{
    long long_dest;                    // Destinatario
    int int_rte;                       // Remitente
    int int_evento;                    // Numero de evento
    int voto_a_candidato;
};

typedef struct tipo_datosThread{
    int idThread;
    int id_cola_mensajes;
    int output_evento;
}datosThread;

typedef enum
{
    MSG_NADIE, //0
    MSG_PANEL, //1
    MSG_VOTANTE // 2 Cada hilo le suma uno a este define.
} Destinos;

typedef enum{
    EVT_NINGUNO, //0
    EV_INIT, //1
    EV_PRESIDENTE, //2
    EV_VICE, //3
    EV_FIN
} Eventos;

// Variable global para semaforo(Mutex)
pthread_mutex_t mutex;

#endif
