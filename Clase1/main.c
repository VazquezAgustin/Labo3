#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "global.h"
#include "funciones.h"
#include <time.h>

int main(int arg, char *argv[])
{
    char cadena[20];
    int entero[2];
    int desde=0, hasta=0;
    
    if (arg == 3){
        desde = atoi(argv[1]);
        hasta = atoi(argv[2]);
    }
    else
    {
        desde = 30;
        hasta = 100;
    }
    srand(time(NULL));
    memset(cadena, 0x00, sizeof(cadena)); /* set memoria */
    printf("primero HOLA");
    memcpy(cadena, "pepe2", 5);
    memcpy(cadena, "1234", 4);
    printf("%s", cadena);
    cadena[0] = '2';
    printf("%02x", cadena[0]);
    strcpy(cadena, ".");
    entero[0] = 0;
    printf("%02x", entero[0]);

    /* varEntero = 0;
    varEntero = 1230;*/

    printf("%d", devolverNumAleatorio(desde, hasta));

    // while(1){
    //     /* scanf("%s", cadena); */
    //     printf("HOLA %s ", cadena);
    //     memset(cadena, 0x00, sizeof(cadena));
    //     /* printf("%d", varEntero); */
    // }

    return 0;
}
