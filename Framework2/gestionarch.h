#ifndef _GESTIONARCH
#define _GESTIONARCH

FILE * AbrirArchivo(FILE *, char *, char []);

void voLeerArchivo(FILE *);

void voEscribirArchivo(FILE *, const char[]);

char *leerPrimeraLinea(FILE *archivo);

void voCerrarArchivo(FILE *);

#endif
