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
        char *linea;
        char *nombre_archivo = (char *)malloc(20 * sizeof(char)); // tamano de la cadena * sizeofchar

        //Leo archivo pedidos
        archivo_pedidos = AbrirArchivo(archivo_pedidos, "r", "pedidos.dat");
        linea = leerPrimeraLinea(archivo_pedidos);
        printf("1; %s", linea);

        //Leo archivo pedidos
        linea = leerPrimeraLinea(archivo_pedidos);
        printf("1; %s", linea);

        //Leo archivo pedidos
        linea = leerPrimeraLinea(archivo_pedidos);
        printf("1; %s", linea);

        voCerrarArchivo(archivo_pedidos);

        return 0;
    }
