#ifndef SHELL_C_COMANDOS_H
#define SHELL_C_COMANDOS_H


#include "cabeceras.h"
#include <libgen.h> // Para el comando <list>
#include <grp.h>    // Para el comando <list>
#include <pwd.h>    // Para el comando <list>

#define MAX_LENGTH 255
#define MAX_INPUT_SIZE 1024
#define MAX_TOKENS 64



int autores(char *tokens[], int ntokens, lista *lista);  // Imprime los nombres, los login o ambas.
int pid(char *tokens[], int ntokens, lista *lista);      // Muestra el pid o el pid padre.
int carpeta(char *tokens[], int ntokens, lista *lista);  // Muestra la carpeta y permite desplazarse a través de los directorios.
int fecha(char *tokens[], int ntokens, lista *lista);    // Imprime la fecha, la hora o ambas.
int hist(char *tokens[], int ntokens, lista *lista);     // Muestra el historial de comando usados.
int comando(char *tokens[], int ntokens, lista *lista);  // Permite ejecutar un comando usado con anterioridad.
int infosis(char *tokens[], int ntokens, lista *lista);  // Enseña la información del sistema: SO, arquitectura, nombre del PC...
int fin(char *tokens[], int ntokens, lista *lista);      // Fin, salir y bye, finalizan la ejecución del programa.
int salir(char *tokens[], int ntokens, lista *lista);
int bye(char *tokens[], int ntokens, lista *lista);

int create(char *tokens[], int ntokens, lista *lista);   // Crea una carpeta o un fichero.
off_t tamanoFichero(char *file);
int printStat(char *tokens, SStatCommand *flags);
int stats(char *tokens[], int ntokens, lista *lista);     //
int list(char *tokens[], int ntokens, lista *lista);     //
int delete(char *tokens[], int ntokens, lista *lista);   // Elimina los ficheros o directorios vacíos que se pasan como parámetro.
int deltree(char *tokens[], int ntokens, lista *lista);  // Elimina los ficheros o directorios vacíos de forma recursiva.


/* Para el comando <list> */
//int printDirInfo(char *dir, struct listOptions *com);
//int listSubDir(char *dir, struct listOptions *com);
//int isDir(const char *path);
//int printFileInfo(char *path, struct listOptions *com);


#endif //SHELL_C_COMANDOS_H
