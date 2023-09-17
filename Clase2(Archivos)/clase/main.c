#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "global.h"
#include "funciones.h"
#include "time.h"

int main(int arg, char *argv[])
{

    if (arg != 2) {
        printf("Uso: debe ingresar <A|B|C> junto a la ejecucion del programa \n");
        return 1;
    }

    int desde=0, hasta=0;

    /* memoria dinamica */
    char *szCadena1;
    char *szCadena2;
    char *szCadena3[20 + 1]; /* un char es de -128 a 127 */
    unsigned char cadena[100+1]; /*256*/

    int *enteroDin;
    short shorts[2];
    int entero;

    entero = malloc(sizeof(int));
    szCadena1 = (char*)malloc(sizeof(char)*5);
    szCadena2 = (char*)malloc(5);
    
    printf("cantidad de argumentos %d \n", arg);

    if (arg == 3){
        desde = atoi(argv[1]);
        hasta = atoi(argv[2]);
        printf(" desde : %d . hasta : %d \n", desde, hasta);
    }
    else
    {
        desde = 30;
        hasta = 100;
    }

    printf("%d \n", devolverNumAleatorio(desde, hasta));

    memset(cadena, 0x00, sizeof(cadena));
    memset(szCadena1, 0x00, sizeof(szCadena1));
    memset(szCadena2, 0x00, sizeof(szCadena2));
    
    sprintf(cadena, "Mi var en cadena: %i", desde);
    memcpy(&szCadena1[0], "FABIO", 5);
    memcpy(&szCadena2[0], "PABLO", 5);

    if(memcmp(&szCadena1[1], &szCadena2[1], 2) == 0){
        printf("SE REPITEN DOS LETRAS: %c %c \n", szCadena1[1], szCadena1[2]);
        printf("SE REPITEN DOS LETRAS: %02x %02x \n", *szCadena1, &szCadena1[2]);
    }
    else
    {
        printf("NO SE REPITEN \n");
    }

    free(szCadena1);
    free(szCadena2);
    free(szCadena3);

    /* memcmp(&szCadena1[0], &szCadena2[0], 3); */
    memcmp(szCadena1, szCadena2, strlen(szCadena2)); /*strlen se corta cuando encuentra 0x00 */

    return 0;
}
