#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaforo.h>
#include <gestionarch.h>
#include <time.h>

int main(int arg, char *argv[])
{
    int menu_deseado = 0;
    char tipo_alumno[2];
    int cantidad_materias = 0;
    char nombre_alumno[30];
    char apellido_alumno[30];


    printf("Ingrese menu deseado (1 para carga alumnos/2 para leer inscriptos) \n");
    scanf("%d", &menu_deseado);
    
    if (menu_deseado == 1)
    {
        // MENU 1
        printf("Tipo de alumno: (I para inicial/M para materias a validar) \n");
        scanf("%c", tipo_alumno);

        if(strcmp(tipo_alumno, "M") == 0){
            printf("Ingrese la cantidad de materias: \n");
            scanf("%d", &cantidad_materias);
        }

        printf("Ingrese nombre del alumno \n");
        memset(nombre_alumno, 0x00, sizeof(nombre_alumno));
        scanf("%s", nombre_alumno);

        printf("Ingrese apellido del alumno \n");
        memset(apellido_alumno, 0x00, sizeof(apellido_alumno));
        scanf("%s", apellido_alumno);
    }
    
    if (menu_deseado == 2)
    {
        // MENU 2
        printf("Tipo de alumno a leer: (I para inicial/M para materias a validar) \n");
        scanf("%c", tipo_alumno);
    }
    

    return 0;
}
