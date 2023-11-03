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
#include "global.h"
#include "mensajes.h"
#include "hormiga.h"

int main(){
    int cantidad_hormigas, id_cola_mensajes, i, maximo_stock = 0;
    datosHormiga *datos_hormiga = NULL;
    pthread_t *idHormiga = NULL;
    pthread_attr_t atributos;
    Insumo insumos[CANTIDAD_INSUMOS];
    mensaje mensaje;
    
    do{
        printf("Cantidad de hormigas (minimo 2): ");
        scanf("%d", &cantidad_hormigas);
    }while (cantidad_hormigas < 2);

    for (i=0; i<CANTIDAD_INSUMOS; i++){
        insumos[i].insumo = i;
        insumos[i].stock = 0;
    }

    printf("\nINSUMOS:");
    for (i=0; i<CANTIDAD_INSUMOS; i++){
        printf("\ninsumo: %d\tstock: %d", insumos[i].insumo, insumos[i].stock);
    }
    printf("\n");

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_COLA);
    borrar_mensajes(id_cola_mensajes);

    pthread_mutex_init(&mutex, NULL);
    
    idHormiga = (pthread_t *)malloc(sizeof(pthread_t)*cantidad_hormigas);
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    datos_hormiga = (datosHormiga *)malloc(sizeof(datosHormiga)*cantidad_hormigas);

    printf("\nDATOS HORMIGAS");
    for (i=0; i<cantidad_hormigas; i++){
        datos_hormiga[i].idHormiga = MSG_HORMIGA + i;
        datos_hormiga[i].id_cola_mensajes = id_cola_mensajes;
        printf("\nidHormiga: %d\tid_cola_mensajes: %d", datos_hormiga[i].idHormiga, datos_hormiga[i].id_cola_mensajes);
        pthread_create(&idHormiga[i], &atributos, threadHormiga, &datos_hormiga[i]);
    }
    printf("\n");

    srand(time(NULL));

    while (maximo_stock < 100){

        pthread_mutex_lock(&mutex);
            for (i=0; i<cantidad_hormigas; i++){
                mensaje.insumo = 0 + (rand() % ((CANTIDAD_INSUMOS-1) - 0 + 1));
                mensaje.dest = MSG_HORMIGA + i;
                mensaje.src = MSG_REINA;
                mensaje.cantidad = 0;
                enviar_mensaje(id_cola_mensajes, mensaje.dest, mensaje.src, mensaje.insumo, mensaje.cantidad);
                printf("\nReina envio orden");
            }
            printf("\n");
        pthread_mutex_unlock(&mutex);

        usleep(INTERVALO * 1000);

        for (i=0; i<cantidad_hormigas; i++){
            recibir_mensaje_bloqueante(id_cola_mensajes, MSG_REINA, &mensaje);
            insumos[mensaje.insumo].stock += mensaje.cantidad;
        }
        printf("\n");

        printf("\nINSUMOS JUNTADOS:");
        printf("\n");
        for (i=0; i<CANTIDAD_INSUMOS; i++){
            if (insumos[i].stock > maximo_stock){
                maximo_stock = insumos[i].stock;
            }
            printf("\nIsumo: %d\tjuntado: %d\n", insumos[i].insumo, insumos[i].stock);
        }
        printf("\n");

        usleep(INTERVALO * 1000);

    }

    pthread_mutex_lock(&mutex);
        for (i=0; i<cantidad_hormigas; i++){
            mensaje.dest = MSG_HORMIGA + i;
            mensaje.src = MSG_REINA;
            mensaje.insumo = NADA;
            mensaje.cantidad = 0;
            enviar_mensaje(id_cola_mensajes, mensaje.dest, mensaje.src, mensaje.insumo, mensaje.cantidad);
            printf("\nReina envio mensaje fin");
        }
        printf("\n");
    pthread_mutex_unlock(&mutex);

    free(idHormiga);
    borrar_mensajes(id_cola_mensajes);
    msgctl (id_cola_mensajes, IPC_RMID, NULL);

    printf("\nINSUMOS JUNTADOS:");
    printf("\n");
    for (i=0; i<CANTIDAD_INSUMOS; i++){
        if (insumos[i].stock > maximo_stock){
            maximo_stock = insumos[i].stock;
        }
        printf("\nIsumo: %d\tjuntado: %d\n", insumos[i].insumo, insumos[i].stock);
    }
    printf("\n");

    return 0;
}
