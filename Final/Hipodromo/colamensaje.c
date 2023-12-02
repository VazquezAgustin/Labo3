#include <colamensaje.h>
#include <clave.h>

int creo_id_cola_mensajes(int clave)
{
    int id_cola_mensajes = msgget(creo_clave(clave), 0600 | IPC_CREAT);
    
    if (id_cola_mensajes == -1)
    {
        printf("Error al obtener identificador para cola mensajes\n");
        exit(-1);
    }
    return id_cola_mensajes;
}
int enviar_mensaje(int id_cola_mensajes, long rLongDest, int rIntRte, int rIntEvento, int metros)
{
    mensaje msg;
    msg.long_dest = rLongDest;
    msg.int_rte = rIntRte;
    msg.int_evento = rIntEvento;
    msg.metros = metros;
    return msgsnd(id_cola_mensajes, (struct msgbuf *)&msg, sizeof(msg.int_rte) + sizeof(msg.int_evento) + sizeof(msg.metros), IPC_NOWAIT);
}
int recibir_mensaje(int id_cola_mensajes, long rLongDest, mensaje *rMsg, int bloqueante)
{
    mensaje msg;
    int res;
    res = msgrcv(id_cola_mensajes, (struct msgbuf *)&msg, sizeof(msg.int_rte) + sizeof(msg.int_evento) + sizeof(msg.metros), rLongDest, bloqueante); // 0 bloquenate - 1 no bloqueante
    rMsg->long_dest = msg.long_dest;
    rMsg->int_rte = msg.int_rte;
    rMsg->int_evento = msg.int_evento;
    rMsg->metros = msg.metros;
    return res;
}
int borrar_mensajes(int id_cola_mensajes)
{
    mensaje msg;
    int res;
    do
    {
        res = msgrcv(id_cola_mensajes, (struct msgbuf *)&msg, sizeof(msg.int_rte) + sizeof(msg.int_evento) /*+ sizeof(msg.nro_cuenta) + sizeof(msg.monto) + sizeof(msg.char_mensaje)*/, 0, IPC_NOWAIT);
    } while (res > 0);
    return res;
}
