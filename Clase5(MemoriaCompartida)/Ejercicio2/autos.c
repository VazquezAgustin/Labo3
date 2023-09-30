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
#include <limits.h>

int main(int arg, char *argv[])
{   
    //memoria y semaforos
	int id_memoria;	
	dato *memoria = NULL;
	int id_semaforo;
    //generales
	int contador_for;
    int via_a_llenar = 0;
    int valor_actual = 0;
    int i;
    int minimo_autos = INT_MAX;

    id_semaforo = creo_semaforo();
	memoria = (dato*)creo_memoria(sizeof(dato)*CANTIDAD, &id_memoria, CLAVE_BASE);

	for (contador_for = 0; contador_for < 10; contador_for++) {  // Ejecutar el bucle 10 veces
        valor_actual = (contador_for % 3) + 1; // 1, 2, 3, 1, 2, 3, ...

        espera_semaforo(id_semaforo);
        via_a_llenar = 0;
		for (i=0; i<CANTIDAD_VIAS; i++)
		{
            printf("Via numero %d \n", i);
            // Si la cantidad de vehiculos es menor al minimo identificado, piso mi via a llenar

            if (memoria[i].vehiculos_en_cola < minimo_autos) {
                printf("La via %d tiene %d autos el cual es menor que %d \n", i, memoria[i].vehiculos_en_cola, minimo_autos);
                minimo_autos = memoria[i].vehiculos_en_cola;
                via_a_llenar = i;
            }
        }

        printf("La via a llenar sera %d la cual tiene %d \n", via_a_llenar, memoria[via_a_llenar].vehiculos_en_cola);

        // agrego auto en donde menos habia
        memoria[via_a_llenar].vehiculos_en_cola = memoria[via_a_llenar].vehiculos_en_cola + 1;

        // Restablecer minimo_autos a INT_MAX
        minimo_autos = INT_MAX;
        
        levanta_semaforo(id_semaforo);

		sleep (2);
	}

	shmdt ((char *)memoria);
	shmctl (id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
	return 0;
}
