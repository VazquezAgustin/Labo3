#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <time.h>
#include <string.h>
#include "clave.h"
#include "global.h"
#include "mensajes.h"

int creo_id_cola_mensajes(int clave){
    int id_cola_mensajes = msgget(creo_clave(clave), 0600 | IPC_CREAT);
    if (id_cola_mensajes == -1)
    {
        printf("Error al obtener identificador para cola mensajes\n");
        exit(-1);
    }
    return id_cola_mensajes;
}

int enviar_mensaje(int id_cola_mensajes, long dest, int src, int insumo, int cantidad){
    mensaje msg;
    msg.dest = dest;
    msg.src = src;
    msg.insumo = insumo;
    msg.cantidad = cantidad;
    return msgsnd(id_cola_mensajes, (struct msgbuf *)&msg, sizeof(msg.src) + sizeof(msg.insumo) + sizeof(msg.cantidad), IPC_NOWAIT);
}

int recibir_mensaje_bloqueante(int id_cola_mensajes, long dest, mensaje *rMsg){
    mensaje msg;
    int res;
    res = msgrcv(id_cola_mensajes, (struct msgbuf *)&msg, sizeof(msg.src) + sizeof(msg.insumo) + sizeof(msg.cantidad), dest, 0);
    rMsg->dest = msg.dest;
    rMsg->src = msg.src;
    rMsg->insumo = msg.insumo;
    rMsg->cantidad = msg.cantidad;
    return res;
}

int recibir_mensaje_no_bloqueante(int id_cola_mensajes, long dest, mensaje *rMsg){
    mensaje msg;
    int res;
    res = msgrcv(id_cola_mensajes, (struct msgbuf *)&msg, sizeof(msg.src) + sizeof(msg.insumo) + sizeof(msg.cantidad), dest, IPC_NOWAIT);
    rMsg->dest = msg.dest;
    rMsg->src = msg.src;
    rMsg->insumo = msg.insumo;
    rMsg->cantidad = msg.cantidad;
    return res;
}

int borrar_mensajes(int id_cola_mensajes){
    mensaje msg;
    int res;
    do{
        res = msgrcv(id_cola_mensajes, (struct msgbuf *)&msg, sizeof(msg.src) + sizeof(msg.insumo) + sizeof(msg.cantidad), 0, IPC_NOWAIT);
    }while (res > 0);
    return res;
}
