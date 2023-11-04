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

// Variables de ejercicio
typedef struct cant_insumos insumos;
struct cant_insumos
{
    char tipo_insumo[20];
    int cant_de_insumo;
};

struct thread_data{
   int  nro_hormiga;
   int  id_cola_mensajes;
};

struct thread_data thread_data_info;

// Variable global para semaforo(Mutex)
pthread_mutex_t mutex;

// Variables de cola de mensaje
typedef struct tipo_mensajes mensaje;
struct tipo_mensajes
{
    long long_dest;                    // Destinatario
    int int_rte;                       // Remitente
    int int_evento;                    // Numero de evento
    int cantidad_insumo;               // Cantidad Insumos Hormiga
};

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

#endif
