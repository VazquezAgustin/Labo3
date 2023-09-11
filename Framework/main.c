#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaforo.h>
#include <gestionarch.h>

int main(int arg, char *argv[])
{
    int i = 0;
    int id_semaforo;
    char contenido_archivo[20 + 1]; // +1 para el carácter nulo
    FILE *archivo = NULL;

    id_semaforo = creo_semaforo();

    inicia_semaforo(id_semaforo, VERDE);
    archivo = AbrirArchivo(archivo, "w");

    if(archivo != NULL){
        for (i = 1; i < 10000; ++i)
        {
            espera_semaforo(id_semaforo);
            
            snprintf(contenido_archivo, 12, "AUTO-%d \n", i);
            voEscribirArchivo(archivo, contenido_archivo);
            
            fflush(archivo);
            levanta_semaforo(id_semaforo);
            usleep(1000000);
        }
    }else{
        printf("Error al abrir el archivo para escritura");
    }
    voCerrarArchivo(archivo);
    return 0;
}
