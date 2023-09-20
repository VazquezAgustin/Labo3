    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <clave.h>
    #include <semaforo.h>
    #include <gestionarch.h>
    #include <time.h>

    int main(int arg, char *argv[])
    {
        //semaforos y archivos
        FILE *archivo_origen = NULL;
        FILE *archivo_destino = NULL;
        char nombre_archivo_destino[15];
        int id_semaforo;
        char contenido_archivo[20 + 1];

        //otros
        char tipo_alumno;
        char letra_tipo_alumno[2];
        char *linea;
        char *token;

        if (arg != 2) {
            printf("Uso: Ingresar 1 o 2 como parametro de entrada (1 para Inicial / 2 para provenientes de otra universidad) \n");
            return 1;
        }

        tipo_alumno = atoi(argv[1]);

        memset(letra_tipo_alumno, 0x00, sizeof(letra_tipo_alumno));
        if (tipo_alumno == 1)
        {
            // Alumno inicial sin materias
            printf("Se inicia el proceso para I \n");
            memcpy(nombre_archivo_destino, "iniciales.dat", 13);
            memcpy(letra_tipo_alumno, "I", 1);
            printf("nombre archivo destino %s \n", nombre_archivo_destino);
            printf("letra tipo alumno %s \n", letra_tipo_alumno);
        }
        if (tipo_alumno == 2)
        {
            // Alumno de otra universidad con materias
            printf("Se inicia el proceso para M \n");
            memcpy(nombre_archivo_destino, "materiasp.dat", 13);
            memcpy(letra_tipo_alumno, "M", 1);
            printf("nombre archivo destino %s \n", nombre_archivo_destino);
            printf("letra tipo alumno %s \n", letra_tipo_alumno);

        }

        id_semaforo = creo_semaforo(); 

        while(1)
        {
            // leo de origen y verifico si este proceso debe procesarlo
            espera_semaforo(id_semaforo);
            archivo_origen = AbrirArchivo(archivo_origen, "r", "cargas.dat");
            linea = leerPrimeraLinea(archivo_origen);
            voCerrarArchivo(archivo_origen);
            levanta_semaforo(id_semaforo);

            if (linea != NULL)
            {   

                // envio a destino correspondiente
                espera_semaforo(id_semaforo);
                archivo_destino = AbrirArchivo(archivo_destino, "a", nombre_archivo_destino);
                memset(contenido_archivo, 0x00, sizeof(contenido_archivo));
                snprintf(contenido_archivo, 20, "%s", linea);
                voEscribirArchivo(archivo_destino, contenido_archivo);
                
                // reinicio archivo
                archivo_origen = AbrirArchivo(archivo_origen, "w", "cargas.dat");

                voCerrarArchivo(archivo_origen);
                voCerrarArchivo(archivo_destino);
                levanta_semaforo(id_semaforo);
                
            }
            
            usleep(500 * 1000);
        }
        return 0;
    }
