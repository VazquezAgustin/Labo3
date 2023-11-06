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
    MSG_ARQUERO, //1
    MSG_PATEADOR // 2 Cada hilo le suma uno a este define.
} Destinos;

typedef enum{
    EVT_NINGUNO, //0
    EVT_TIRO, //1
    EVT_GOL, //2
    EVT_PALO, //3
    EVT_TRAVESAÑO, //4
    EVT_FUERA //5
} Eventos;

// Variable global para semaforo(Mutex)
pthread_mutex_t mutex;

#endif
