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
#define METROS_DESDE 800
#define METROS_HASTA 1000

// Variables de ejercicio
typedef struct struct_metros_recorridos metros_recorridos;
struct struct_metros_recorridos
{
    int metros;
};

// Variables de cola de mensaje
typedef struct tipo_mensajes mensaje;
struct tipo_mensajes
{
    long long_dest;                    // Destinatario
    int int_rte;                       // Remitente
    int int_evento;                    // Numero de evento
    int metros;                // Metros totales
};

typedef struct tipo_datosThread{
    int idThread;
    int id_cola_mensajes;
    int output_thread;
}datosThread;

struct tipo_datos
{
    int dato;
};

typedef enum
{
    MSG_NADIE, //0
    MSG_HIPODROMO, //1
    MSG_CABALLO // 2 Cada hilo le suma uno a este define.
} Destinos;

typedef enum{
    EVT_NINGUNO, //0
    EVT_INICIO, //1
    EVT_METROS, //2
    EVT_SIGA, //3
    EVT_CRUZARON_EL_DISCO //4
} Eventos;

// Variable global para semaforo(Mutex)
pthread_mutex_t mutex;

#endif
