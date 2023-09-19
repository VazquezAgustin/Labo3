#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <unistd.h>
#include <gestionarch.h>

char read_buffer[25];

FILE * AbrirArchivo(FILE *archivo, char modo[], char nombre[]){
    
    // Abrir el archivo en modo escritura
    archivo = fopen(nombre, modo);

    // Verificar si el archivo se abrió correctamente
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return NULL;  // Terminar el programa con código de error
    }else{
        return archivo;
    }
}

void voLeerArchivo(FILE *archivo){
    printf("El contenido del archivo es: ");
    // Abrir archivo en modo lectura
    archivo = fopen("productos.txt", "r");

    while (!feof(archivo))
    {
        fscanf(archivo, "%s ", read_buffer);
        printf("%s\n", read_buffer);
    }
}

char *leerPrimeraLinea(FILE *archivo) {
    if (fgets(read_buffer, sizeof(read_buffer), archivo) == NULL) {
        return NULL;
    }

    return read_buffer;
}

void voEscribirArchivo(FILE *archivo, const char contenido[]){
    fprintf(archivo, "%s", contenido);
}

void voCerrarArchivo(FILE *archivo){
    fclose(archivo);
}
