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
    int id_cola_mensajes;
    mensaje msg;
    //comunes
    int index_iniciar_threads = 0;
    int cantidad_caballos = 0;
    int metros_totales = 0;
    int hay_ganador = 0;
    int mensaje_recibido = 0;
    metros_recorridos array_metros_recorridos[40];

    if (arg == 2){
        cantidad_caballos = MSG_CABALLO + atoi(argv[1]);
    }else
    {
        printf("Uso: Ingresar numero de caballos (max 40) \n");
        exit(-1);
    }

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    borrar_mensajes(id_cola_mensajes);
    
    srand(time(NULL));
    metros_totales = 100;//rand() % (METROS_HASTA - METROS_DESDE + 1) + METROS_DESDE;
    printf("Número aleatorio entre 800 y 1000: %d\n", metros_totales);

    for (index_iniciar_threads = 0; index_iniciar_threads < cantidad_caballos; index_iniciar_threads++)
    {
        // Enviar mensaje
        msg.int_evento = EVT_INICIO;
        msg.long_dest = MSG_CABALLO + index_iniciar_threads;
        msg.int_rte = MSG_HIPODROMO;
        msg.metros = metros_totales;
        enviar_mensaje(id_cola_mensajes, msg.long_dest, msg.int_rte, msg.int_evento, msg.metros);
        printf("Mensaje inicio a caballo thread %ld enviado\n", msg.long_dest);

        // Iniciar estructura para guardar metros
        array_metros_recorridos[index_iniciar_threads].metros = 0;
    }

    printf("Array metros recorridos: \n");
    for (index_iniciar_threads = MSG_CABALLO; index_iniciar_threads < cantidad_caballos ; index_iniciar_threads++)
    {
        printf("Caballo %d - %d \n", index_iniciar_threads, array_metros_recorridos[index_iniciar_threads].metros);
    }

    while (hay_ganador == 0)
    {
        printf("Espero %d\n", mensaje_recibido);
        if (mensaje_recibido != -1){

            switch (msg.int_evento)
            {
            case EVT_METROS:
                array_metros_recorridos[msg.int_rte].metros = array_metros_recorridos[msg.int_rte].metros + msg.metros;
                if (array_metros_recorridos[msg.int_rte].metros >= metros_totales)
                {
                    // termina la carrera
                    msg.int_evento = EVT_CRUZARON_EL_DISCO;
                    msg.int_rte = MSG_HIPODROMO;
                    msg.metros = msg.long_dest; //ENVIA EL GANADOR
                    printf("Termina la carrera - Caballo %ld gano\n", msg.long_dest);

                    for (index_iniciar_threads = MSG_CABALLO; index_iniciar_threads < cantidad_caballos ; index_iniciar_threads++)
                    {
                        // envio mensaje a todos los caballos para que temrinen
                        enviar_mensaje(id_cola_mensajes, index_iniciar_threads, msg.int_rte, msg.int_evento, msg.metros);
                    }

                    hay_ganador = 1;

                }else{
                    // siga
                    msg.int_evento = EVT_SIGA;
                    msg.long_dest = msg.int_rte;
                    msg.int_rte = MSG_HIPODROMO;
                    msg.metros = 0;
                    enviar_mensaje(id_cola_mensajes, msg.long_dest, msg.int_rte, msg.int_evento, msg.metros);
                    printf("Siga corriendo - Caballo %ld\n", msg.long_dest);
                }
                sleep(1);

                printf("---------------------- \n");
                printf("Array metros recorridos: \n");
                for (index_iniciar_threads = MSG_CABALLO; index_iniciar_threads < cantidad_caballos ; index_iniciar_threads++)
                {
                    printf("Caballo %d - %d \n", index_iniciar_threads, array_metros_recorridos[index_iniciar_threads].metros);
                }
                            
                break;
            
            default:
                printf("Evento no definido \n");
                break;
            }            

            mensaje_recibido = recibir_mensaje(id_cola_mensajes, MSG_HIPODROMO, &msg, 1);
        }
    }
    
    borrar_mensajes(id_cola_mensajes);
    msgctl (id_cola_mensajes, IPC_RMID, NULL);

    return 0;
}
