#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "gestionarchivos.h"

char read_buffer[20 + 1];

FILE * AbrirArchivo(FILE *archivo, char modo[]){
    
    // Abrir el archivo en modo escritura
    archivo = fopen("productos.txt", modo);

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

void voEscribirArchivo(FILE *archivo, const char contenido[]){
    fprintf(archivo, "%s", contenido);
}

void voCerrarArchivo(FILE *archivo){
    fclose(archivo);
}
