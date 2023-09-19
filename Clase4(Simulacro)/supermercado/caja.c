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
        int id_semaforo;
        FILE *archivo_productos = NULL;
        char *linea;
        char minimo_caja;
        char maximo_caja;
        int contador = 0;
        char *token;
        char *token_copy;
        int total_compra = 0;
        FILE *archivo = NULL;

        if (arg != 3) {
            printf("Uso: <Minimo> y <Maximo> como parametro de entrada \n");
            return 1;
        }

        minimo_caja = atoi(argv[1]);
        maximo_caja = atoi(argv[2]);

        id_semaforo = creo_semaforo(); 
        
        while (1)
        {
            contador = 0;
            linea = NULL;

            espera_semaforo(id_semaforo);
            archivo_productos = AbrirArchivo(archivo_productos, "r", "productos.dat");

            // calculo la cantidad de producots
            linea = leerPrimeraLinea(archivo_productos);
            voCerrarArchivo(archivo_productos);

            token = strtok(linea, ";");
            while (token != NULL) {
                // Obtenemos el siguiente elemento
                token = strtok(NULL, ";");
                contador = contador + 1;
            }

            token = NULL;
            // verifico si es la caja correspondiente
            if (contador >= minimo_caja && contador <= maximo_caja)
            {
                printf("El proceso desde %d hasta %d acepto el cliente \n", minimo_caja, maximo_caja);
                archivo_productos = NULL;
                
                //Abro el archivo nuevamente para procesar
                archivo_productos = AbrirArchivo(archivo_productos, "r", "productos.dat");

                linea = leerPrimeraLinea(archivo_productos);

                archivo = AbrirArchivo(archivo, "w", "productos.dat");
                archivo = NULL;
                voCerrarArchivo(archivo);

                voCerrarArchivo(archivo_productos);
                levanta_semaforo(id_semaforo);

                token = strtok(linea, ";");
                while (token != NULL) {

                    token_copy = strdup(token); //copio la linea para no perderla al hacer el strtok

                    // Utilizamos strtok para dividir token en nombre y precio
                    token_copy = strtok(token_copy, ",");
                    printf("Nombre: %s\n", token_copy);

                    token_copy = strtok(NULL, ",");
                    printf("Precio: %s\n", token_copy);
                    
                    printf("Valor token %s \n", token);
                    printf("Valor token copy %s \n", token_copy);
                    total_compra = total_compra + atoi(token_copy);

                    // Obtenemos el siguiente elemento
                    token = strtok(NULL, ";");
                }
                    
                printf("Total de la compra es: %d \n", total_compra);

            }else{
                levanta_semaforo(id_semaforo);
            }
            usleep(100 * 1000);
        }

        return 0;
    }
