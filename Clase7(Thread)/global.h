#include <pthread.h> // Libreria Hilos para C

#ifndef _DEFINICIONES_H 
#define _DEFINICIONES_H 

#define LARGO_DESCRIPCION 100 
#define CANT_SEMAFORO 1

#define LARGO_TMENSAJE 1024
#define CANTIDAD_THREADS 3

// Variable global para semaforo(Mutex)
pthread_mutex_t mutex;

typedef struct tipo_mensajes mensaje;
struct tipo_mensajes
{
    long long_dest; //Destinatario
    int int_rte; //Remitente
    int int_evento; //Numero de nevento
    char char_mensaje[LARGO_TMENSAJE]; //mensajse
};

typedef struct tipo_datos datos; 
struct tipo_datos
{
    int dato;
};

typedef enum
{
    MSG_NADIE,
    MSG_BANCO,
    MSG_CAJERO_01,
    MSG_CAJERO_02,
    MSG_CAJERO_03
}Destinos;

typedef enum{
    EVT_NINGUNO, // dejo el ninguno?

    EVT_CONSULTA_SALDO, //Importa el orden de los eventos? o pueden estar en cuaqluier orden
    EVT_RTA_SALDO,
    EVT_RTA_SALDO_NOK,

    EVT_DEPOSITO,
    EVT_RTA_DEPOSITO_OK,
    EVT_RTA_DEPOSITO_NOK,

    EVT_EXTRACCION,
    EVT_RTA_EXTRACCION_OK,
    EVT_RTA_EXTRACCION_NOK
}Eventos;

// GENERALES PARA EL EJERCICIO

typedef struct Cliente dato;

struct Cliente
{
    int codigo_cliente;
    int saldo;
};


#endif
