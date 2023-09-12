#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <clave.h>
#include <semaforo.h>
#include <gestionarch.h>

int main(int arg, char *argv[])
{
    int id_semaforo;
    FILE *archivo = NULL;

    id_semaforo = creo_semaforo();
    archivo = AbrirArchivo(archivo, "r");

    if(archivo != NULL){
        while (1)
        {
            espera_semaforo(id_semaforo);
            voLeerArchivo(archivo);
            levanta_semaforo(id_semaforo);
        }
    }

    return 0;
}
