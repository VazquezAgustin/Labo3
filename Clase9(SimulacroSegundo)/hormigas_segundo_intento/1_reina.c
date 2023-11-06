#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <memoria.h>
#include <semaforo.h>
#include <time.h>
#include <gestionarch.h>
#include <global.h>
#include <colamensaje.h>
#include <funcionthreads.h>

int main(int arg, char *argv[])
{   
    // memoria y semaforo
    pthread_attr_t atributos;
    int id_cola_mensajes;
    mensaje msg;
    datosThread *datos_thread = NULL;
    pthread_t *idThread = NULL;
    //comunes
    int cantidad_hormigas = 0;
    int index_inicializar_cantidad = 0;
    char nombre_insumos[4][20] = {
        "Madera",
        "Hojas",
        "Comida",
        "Rocas"
    };
    struct tipo_insumos lista_insumo[4];
    int index_creacion_threads = 0;
    int user_input = 0;
    int nro_hormiga = 0;
    int terminar = 0;

    // input usuario
    if (arg == 2){
        cantidad_hormigas = atoi(argv[1]);
    }else{
        printf("Uso: enviar <int> junto al ejecutable para definir cantidad de hormigas.\n");
        return 1;
    }

    // inicializar cantidad de insumo en 0
    for (index_inicializar_cantidad = 0; index_inicializar_cantidad < 4; index_inicializar_cantidad++)
    {
        strcpy(lista_insumo[index_inicializar_cantidad].insumo, nombre_insumos[index_inicializar_cantidad]);
        lista_insumo[index_inicializar_cantidad].stock = 0;
    }
    
    for (index_inicializar_cantidad = 0; index_inicializar_cantidad < 4; index_inicializar_cantidad++)
    {
        printf("------ \n");
        printf("%s \n", lista_insumo[index_inicializar_cantidad].insumo);
        printf("%d \n", lista_insumo[index_inicializar_cantidad].stock);
    }

    // Preparo el terreno para los threads
    idThread = (pthread_t *)malloc(sizeof(pthread_t)*cantidad_hormigas);
    datos_thread = (datosThread *)malloc(sizeof(datosThread)*cantidad_hormigas);
    pthread_mutex_init(&mutex, NULL);
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);
    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

    // Crear N cantidad de threadhormiga
    datos_thread = (datosThread *)malloc(sizeof(datosThread)*cantidad_hormigas);

    for (index_creacion_threads=0; index_creacion_threads<cantidad_hormigas; index_creacion_threads++){
        datos_thread[index_creacion_threads].idThread = MSG_HORMIGA + index_creacion_threads;
        datos_thread[index_creacion_threads].id_cola_mensajes = id_cola_mensajes;
        datos_thread[index_creacion_threads].output_evento = 0; // las hormigas no devuelven nada asi que no se usa
        printf("idHormiga: %d\tid_cola_mensajes: %d \n", datos_thread[index_creacion_threads].idThread, datos_thread[index_creacion_threads].id_cola_mensajes);
        pthread_create(&idThread[index_creacion_threads], &atributos, funcionThread, &datos_thread[index_creacion_threads]);
    }

    // while hasta que cualquiera de los materiales sea 90
    while (terminar == 0)
    {
        printf("Ingrese\n1.Madera\n2.Hojas\n3.Comida\n4.Rocas\n");
        scanf("%d", &user_input);

        usleep(500 * 1000);

        pthread_mutex_lock(&mutex);
            msg.tipo_insumo = user_input; // evento
            msg.cantidad = 0;
            if(nro_hormiga == cantidad_hormigas){
                nro_hormiga = 0;
            }else
            {
                nro_hormiga ++;
            }
            
            msg.long_dest = MSG_HORMIGA + nro_hormiga;
            msg.int_rte = MSG_REINA;
            enviar_mensaje(id_cola_mensajes, msg.long_dest, msg.int_rte, msg.tipo_insumo, msg.cantidad);
            printf("\nA Reina envio mensaje %d", msg.tipo_insumo);

            printf("\n");
        pthread_mutex_unlock(&mutex);

        recibir_mensaje(id_cola_mensajes, MSG_REINA, &msg, 0);
        lista_insumo[msg.tipo_insumo].stock = lista_insumo[msg.tipo_insumo].stock + msg.cantidad ;

        for (index_inicializar_cantidad = 0; index_inicializar_cantidad < 4; index_inicializar_cantidad++)
        {
            printf("------ \n");
            printf("%s %d\n", lista_insumo[index_inicializar_cantidad].insumo, lista_insumo[index_inicializar_cantidad].stock);

            if(lista_insumo[index_inicializar_cantidad].stock >= 90)
            {
                printf("insumo %s - %d es mayor a 90, terminando.", lista_insumo[index_inicializar_cantidad].insumo, lista_insumo[index_inicializar_cantidad].stock);
                terminar = 1;
            }
        }
    }

    for (index_creacion_threads=0; index_creacion_threads<cantidad_hormigas; index_creacion_threads++){
        pthread_join (idThread[index_creacion_threads], NULL);
        // printf("Hormiga: %d resultado: %d \n", datos_thread[index_creacion_threads].idThread, datos_thread[index_creacion_threads].output_evento); // hormiga no devuelve nada, por ende no se usa
    }

    free(idThread);
    borrar_mensajes(id_cola_mensajes);
    msgctl (id_cola_mensajes, IPC_RMID, NULL);

    return 0;
}
