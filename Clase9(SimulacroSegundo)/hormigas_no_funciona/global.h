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

typedef enum
{
    MSG_NADIE,
    MSG_HORMIGA_REINA,
    MSG_HORMIGA_1,
    MSG_HORMIGA_2,
    MSG_HORMIGA_3
} Destinos;

struct tipo_datos
{
    int dato;
};

typedef enum
{
    EVT_NINGUNO,
    EVT_RECOLECTAR_MADERA,
    EVT_RECOLECTAR_HOJAS,
    EVT_RECOLECTAR_COMIDA,
    EVT_RECOLECTAR_SEMILLA,
    EVT_GUARDAR_MADERA,
    EVT_GUARDAR_HOJAS,
    EVT_GUARDAR_COMIDA,
    EVT_GUARDAR_SEMILLA
} Eventos;

#endif
