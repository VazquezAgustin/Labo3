#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i;
    char contenido_archivo[20 + 1]; // +1 para el carácter nulo
    FILE *archivo;

    // Abrir el archivo en modo escritura
    if(inAbrirArchivo(&archivo, "w") == 0){
        // Escribir el archivo
        for (i = 1; i < 11; ++i)
        {
            snprintf(contenido_archivo, 12, "AUTO-%d \n", i);
            voEscribirArchivo(archivo, contenido_archivo);
        }
        voCerrarArchivo(archivo);
    };

    // Leer archivo
    if(inAbrirArchivo(&archivo, "r") == 0){
        voLeerArchivo(archivo);
        // Cerrar archivo
        voCerrarArchivo(archivo);
    }
}
