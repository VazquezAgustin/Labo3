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

        char tipo_alumno;

        if (arg != 2) {
            printf("Uso: Ingresar 1 o 2 como parametro de entrada (1 para Inicial / 2 para provenientes de otra universidad) \n");
            return 1;
        }

        tipo_alumno = atoi(argv[1]);

        return 0;
    }
