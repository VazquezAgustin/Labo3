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
    FILE *archivo_pedidos = NULL;
    FILE *archivo_productor = NULL;
    char *contenido_archivo = NULL; // +1 para el carácter nulo
    char *linea = NULL;

    id_semaforo = creo_semaforo();

    while (1)
    {
        espera_semaforo(id_semaforo);

        // Leo archivo pedidos
        archivo_pedidos = AbrirArchivo(archivo_pedidos, "r", "pedidos.dat");
        linea = leerLineaDeArchivo(archivo_pedidos);

        archivo_productor = AbrirArchivo(archivo_productor, "w", "productora.dat");
        snprintf(contenido_archivo, 50, "%s", linea);
        voEscribirArchivo(archivo_productor, contenido_archivo);

        printf("%s", linea);

        voCerrarArchivo(archivo_pedidos);
        levanta_semaforo(id_semaforo);
    }

    return 0;
}
