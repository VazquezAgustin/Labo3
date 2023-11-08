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
int enviar_mensaje(int id_cola_mensajes, long rLongDest, int rIntRte, int rIntEvento, int voto_a_candidato)
{
    mensaje msg;
    msg.long_dest = rLongDest;
    msg.int_rte = rIntRte;
    msg.int_evento = rIntEvento;
    msg.voto_a_candidato = voto_a_candidato;
    return msgsnd(id_cola_mensajes, (struct msgbuf *)&msg, sizeof(msg.int_rte) + sizeof(msg.int_evento) + sizeof(msg.voto_a_candidato), IPC_NOWAIT);
}
int recibir_mensaje(int id_cola_mensajes, long rLongDest, mensaje *rMsg, int bloqueante)
{
    mensaje msg;
    int res;
    res = msgrcv(id_cola_mensajes, (struct msgbuf *)&msg, sizeof(msg.int_rte) + sizeof(msg.int_evento) + sizeof(msg.voto_a_candidato), rLongDest, bloqueante); // 0 bloquenate - 1 no bloqueante
    rMsg->long_dest = msg.long_dest;
    rMsg->int_rte = msg.int_rte;
    rMsg->int_evento = msg.int_evento;
    rMsg->voto_a_candidato = msg.voto_a_candidato;
    return res;
}
int borrar_mensajes(int id_cola_mensajes)
{
    mensaje msg;
    int res;
    do
    {
        res = msgrcv(id_cola_mensajes, (struct msgbuf *)&msg, sizeof(msg.int_rte) + sizeof(msg.int_evento) + sizeof(msg.voto_a_candidato), 0, IPC_NOWAIT);
    } while (res > 0);
    return res;
}
