#ifndef _GESTIONARCH
#define _GESTIONARCH

int inAbrirArchivo(FILE **archivo, const char *modo);

void voLeerArchivo(FILE *archivo);

void voEscribirArchivo(FILE *archivo, const char[]);

void voCerrarArchivo(FILE *archivo);

#endif
