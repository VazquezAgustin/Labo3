#ifndef GLOBAL_H
#define GLOBAL_H

#include <pthread.h>

#define CLAVE_COLA 33
#define MAXIMO_INSUMOS 6
#define MINIMO_INSUMOS 1
#define CANTIDAD_INSUMOS 4
#define INTERVALO 300

typedef struct tipo_mensaje{
    long dest;
    int src;
    int insumo;
    int cantidad;
}mensaje;

typedef struct tipo_datosHormiga{
    int idHormiga;
    int id_cola_mensajes;
}datosHormiga;

typedef struct tipo_insumo{
    int insumo;
    int stock;
}Insumo;

typedef enum{
    MSG_NADIE,
    MSG_REINA,
    MSG_HORMIGA
}Destinos;

typedef enum{
    HOJAS,
    PALITOS,
    COMIDA,
    PIEDRITAS,
    NADA
}NombreInsumos;

extern pthread_mutex_t mutex;

#endif
