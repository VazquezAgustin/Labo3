#ifndef _FUNCIONES_H
#define _FUNCIONES_H
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
typedef struct tipo_mensajes mensaje;
struct tipo_mensajes
{
    long long_dest;                    // Destinatario
    int int_rte;                       // Remitente
    int int_evento;                    // Numero de evento
    int nro_cuenta;                    // numero de cuenta
    int monto;                         // monto en la cuenta
    char char_mensaje[LARGO_TMENSAJE]; // mensaje
};

// Variable global para semaforo(Mutex)
pthread_mutex_t mutex;

struct thread_data{
   int  numero_aleatorio;
   int  alguien_acerto;
   int  cantidad_threads;
};

struct thread_data thread_data_info;

#endif
