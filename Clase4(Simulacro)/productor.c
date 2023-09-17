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
        char letra_binario;
        int contador = 0;

        if (arg != 2) {
            printf("Uso: enviar <A|B|C> junto a la ejecucion del programa \n");
            return 1;
        }

        letra_binario = argv[1][0];

        id_semaforo = creo_semaforo();
        sprintf(nombre_archivo, "productor-%c.dat", letra_binario);
        archivo_productor = AbrirArchivo(archivo_productor, "w", nombre_archivo);

        while(1)
        {
            espera_semaforo(id_semaforo);

            //Leo archivo pedidos
            archivo_pedidos = AbrirArchivo(archivo_pedidos, "r", "pedidos.dat");
            linea = leerPrimeraLinea(archivo_pedidos);
            printf("LA LINEA ES %s", linea);

            voEscribirArchivo(archivo_productor, linea);
            
            voCerrarArchivo(archivo_pedidos);
            contador = contador + 1;
            levanta_semaforo(id_semaforo);
        }

        voCerrarArchivo(archivo_productor);

        return 0;
    }
