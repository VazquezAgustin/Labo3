#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaforo.h>
#include <gestionarch.h>
#include <time.h>

// Definición de la estructura
struct Producto {
    char descripcion[20];
    int precio;
};

int main(int arg, char *argv[])
{
    struct Producto productos[40];
    int salir = 0; // Cambiado a 0 para salir cuando se ingresa 0

    int id_semaforo;
    int contador = 0;
    char contenido_archivo[20 + 1]; // +1 para el carácter nulo
    FILE *archivo = NULL;
    int i = 0;

    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);

    archivo = AbrirArchivo(archivo, "w", "productos.dat");

    while (1)
    {
        sleep(1);
        
        salir = 0;
        while (salir == 0)
        {
            printf("Ingrese el producto (Ingrese 0 para salir): \n");
            scanf("%s", productos[contador].descripcion);

            if (strcmp(productos[contador].descripcion, "0") != 0) // no quiere salir
            {
                // precio
                printf("Ingrese el precio: \n");
                scanf("%d", &productos[contador].precio);

                contador = contador + 1;
                printf("afuera");

            }else{
                salir = 1; // Salir del bucle
                printf("else");
            }
        }

        
        espera_semaforo(id_semaforo);
        archivo = AbrirArchivo(archivo, "w", "productos.dat");

        for (i = 0; i < contador; i++) {
            snprintf(contenido_archivo, 20, "%s,%d;", productos[i].descripcion, productos[i].precio);
            voEscribirArchivo(archivo, contenido_archivo);
        }

        voCerrarArchivo(archivo);
        levanta_semaforo(id_semaforo);
    }
    
    

    
}
