#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaforo.h>
#include <gestionarch.h>

// Definición de la estructura
struct Pedido {
    char menu[1 + 1];
    int postre;
    int precio;
};

int main(int arg, char *argv[])
{
    struct Pedido pedidos[3];
    int precio_postre = 0;
    int precio_menu = 0;
    int postre;
    int numeroAleatorio;
    int precio_total = 0;

    int id_semaforo;
    char contenido_archivo[20 + 1]; // +1 para el carácter nulo
    FILE *archivo = NULL;

    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);

    // relleno estructura
    strcpy(pedidos[0].menu, "A");
    strcpy(pedidos[1].menu, "B");
    strcpy(pedidos[2].menu, "C");

    // Inicializar la semilla para los números aleatorios
    srand(time(NULL));

    while (1)
    {
        espera_semaforo(id_semaforo);
        
        // Generar un número aleatorio en el rango de 0 a 2
        numeroAleatorio = rand() % 3; // 0, 1 o 2

        // calculo precio
        if(strcmp(pedidos[numeroAleatorio].menu, "A") == 0){
            precio_menu = 1000;
        }
        if(strcmp(pedidos[numeroAleatorio].menu, "B") == 0){
            precio_menu = 2000;
        }
        if(strcmp(pedidos[numeroAleatorio].menu, "C") == 0){
            precio_menu = 3000;
        }

        printf("Desea postre? (1 si, 0 no): \n");
        scanf("%d", &postre);

        pedidos[numeroAleatorio].postre = postre;

        if(postre == 1){
            precio_postre = 200;
        }else{
            precio_postre = 0;
        }

        precio_total = precio_menu + precio_postre;
        pedidos[numeroAleatorio].precio = precio_total;

        archivo = AbrirArchivo(archivo, "w", "pedidos.dat");
        snprintf(contenido_archivo, 20, "%s,%d,%d\n", pedidos[numeroAleatorio].menu, pedidos[numeroAleatorio].postre, pedidos[numeroAleatorio].precio);
        printf("LINEA ES %s", contenido_archivo);
        voEscribirArchivo(archivo, contenido_archivo);

        voCerrarArchivo(archivo);
        levanta_semaforo(id_semaforo);
        usleep(1000 * 1000);
    }
}
