#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <memoria.h>
#include <semaforo.h>
#include <time.h>
#include <gestionarch.h>
#include <global.h>

int main(int arg, char *argv[])
{   
    // memoria y semaforo
    int id_memoria;
    dato *memoria = NULL;
    int id_semaforo;
    FILE *archivo = NULL;
    //comunes
    //struct Via vias[CANTIDAD_VIAS] = {{0}, {0}, {0}}; // Inicialización estática
    int duracion_aleatoria;
    int contador_for;
    int valor_actual;
    int via;
    int contador_mas_10 = 0;

    // Inicializaciones
    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);
    memoria = (dato*)creo_memoria(sizeof(dato)*CANTIDAD, &id_memoria, CLAVE_BASE);
    srand(time(NULL));
    duracion_aleatoria = rand()%(100-5000);

    //Inicializar estructura
    for (via = 0; via < CANTIDAD_VIAS; via++)
    {
        memoria[via].vehiculos_en_cola = 0;
    }

    for (contador_for = 0; contador_for < 10; contador_for++) {  // Ejecutar el bucle 10 veces
        espera_semaforo(id_semaforo);
        valor_actual = (contador_for % 3) + 1; // 1, 2, 3, 1, 2, 3, ...

        if(memoria[valor_actual - 1].vehiculos_en_cola >= 10){
            memoria[valor_actual - 1].vehiculos_en_cola = 0;
            contador_mas_10 ++;
            archivo = AbrirArchivo(archivo, "w", "cantidad_10_autos.dat");
        }
        else if(memoria[valor_actual - 1].vehiculos_en_cola >0)
        {
            memoria[valor_actual - 1].vehiculos_en_cola--;
        }

        for (via = 0; via < CANTIDAD_VIAS; via++)
        {
            printf("VIA[%d]:    %d Vehiculos \n", via + 1 ,memoria[via].vehiculos_en_cola);
        }
        printf("------------------------- \n");
        
        levanta_semaforo(id_semaforo);
        // usleep(duracion_aleatoria);
        sleep(2);
    }

    shmdt ((char *)memoria);
	shmctl (id_memoria, IPC_RMID, (struct shmid_ds *)NULL);

    return 0;
}
