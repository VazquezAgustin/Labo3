#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaforo.h>
#include <gestionarch.h>
#include <time.h>

int main(int arg, char *argv[])
{
    //archivos y semaforo
    int id_semaforo = 0;
    char contenido_archivo[20 + 1];
    FILE *archivo = NULL;
    FILE *archivo_lectura = NULL;

    // otras
    int menu_deseado = 0;
    char tipo_alumno[2];
    char tipo_alumno_lectura[2];
    int cantidad_materias = 0;
    char nombre_alumno[30];
    char apellido_alumno[30];

    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);

    // creando archivo vacio
    archivo = AbrirArchivo(archivo, "w", "cargas.dat");
    voCerrarArchivo(archivo);

    while (1)
    {

        printf("Ingrese menu deseado (1 para carga alumnos/2 para leer inscriptos) \n");
        scanf("%d", &menu_deseado);
        
        if (menu_deseado == 1)
        {
            // MENU 1
            printf("Tipo de alumno: (I para inicial/M para materias a validar) \n");
            memset(tipo_alumno, 0x00, sizeof(tipo_alumno));
            scanf("%s", tipo_alumno);

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

            // enviar a archivo
            espera_semaforo(id_semaforo);
            archivo = AbrirArchivo(archivo, "w", "cargas.dat");

            memset(contenido_archivo, 0x00, sizeof(contenido_archivo));
            snprintf(contenido_archivo, 20, "%s,%d,%s,%s", tipo_alumno, cantidad_materias, nombre_alumno, apellido_alumno);
            voEscribirArchivo(archivo, contenido_archivo);

            voCerrarArchivo(archivo);
            levanta_semaforo(id_semaforo);
        }
        
        if (menu_deseado == 2)
        {
            // MENU 2
            printf("Tipo de alumno a leer: (I para inicial/M para materias a validar) \n");
            memset(tipo_alumno_lectura, 0x00, sizeof(tipo_alumno_lectura));
            scanf("%s", tipo_alumno_lectura);

            espera_semaforo(id_semaforo);
            if(strcmp(tipo_alumno_lectura, "M") == 0){
                archivo_lectura = AbrirArchivo(archivo_lectura, "r", "materiasp.dat");
            }

            if(strcmp(tipo_alumno_lectura, "I") == 0){
                archivo_lectura = AbrirArchivo(archivo_lectura, "r", "iniciales.dat");
            }

            printf("aca 3 ");
            voLeerArchivo(archivo_lectura);
            voCerrarArchivo(archivo_lectura);
            levanta_semaforo(id_semaforo);
        }
    }

    return 0;
}
