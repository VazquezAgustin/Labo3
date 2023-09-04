#include <stdio.h>
#include <stdlib.h>

int main(int arg, char *argv[])
{
    int i;
    char contenido_archivo[20 + 1]; // +1 para el carácter nulo
    FILE *archivo = NULL;

    // Abrir el archivo en modo escritura
    archivo = AbrirArchivo(archivo, "w");

    if(archivo != NULL){
        // Escribir el archivo
        for (i = 1; i < 11; ++i)
        {
            snprintf(contenido_archivo, 12, "AUTO-%d \n", i);
            voEscribirArchivo(archivo, contenido_archivo);
        }
        voCerrarArchivo(archivo);
    }else{
        printf("Error al abrir el archivo para escritura");
    };

    // Leer archivo
    archivo = AbrirArchivo(archivo, "r");
    if(archivo != NULL){
        voLeerArchivo(archivo);
        // Cerrar archivo
        voCerrarArchivo(archivo);
    }else{
        printf("Error al abrir el archivo para lectura");
    }
}
