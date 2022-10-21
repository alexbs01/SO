/*
    Login: a.becerra
    Login: adrian.rego
    Nombre: Alejandro Becerra Suarez
    Nombre: Adrián Rego Criado
*/
#ifndef SHELL_C_COMANDOS_H
#define SHELL_C_COMANDOS_H

#include "funcionesAuxiliares.h"
#include "cabeceras.h"
#include <libgen.h> // Para el comando <list>
#include <grp.h>    // Para el comando <list>
#include <pwd.h>    // Para el comando <list>


#include "lista.h"

#define MAX_LENGTH 255
#define MAX_INPUT_SIZE 1024
#define MAX_TOKENS 64

int autores(char *tokens[], int ntokens, lista *listas);  // Imprime los nombres, los login o ambas.
int pid(char *tokens[], int ntokens, lista *listas);      // Muestra el pid o el pid padre.
int carpeta(char *tokens[], int ntokens, lista *listas);  // Muestra la carpeta y permite desplazarse a través de los directorios.
int fecha(char *tokens[], int ntokens, lista *listas);    // Imprime la fecha, la hora o ambas.
int hist(char *tokens[], int ntokens, lista *listas);     // Muestra el historial de comando usados.
int comando(char *tokens[], int ntokens, lista *listas);  // Permite ejecutar un comando usado con anterioridad.
int infosis(char *tokens[], int ntokens, lista *listas);  // Enseña la información del sistema: SO, arquitectura, nombre del PC...
int fin(char *tokens[], int ntokens, lista *listas);      // Fin, salir y bye, finalizan la ejecución del programa.
int salir(char *tokens[], int ntokens, lista *listas);
int bye(char *tokens[], int ntokens, lista *listas);

int create(char *tokens[], int ntokens, lista *listas);   // Crea una carpeta o un fichero.
int stats(char *tokens[], int ntokens, lista *listas);    // Retorna datos del archivo
int list(char *tokens[], int ntokens, lista *listas);     // Retorna los datos de los archivos del directorio
int delete(char *tokens[], int ntokens, lista *listas);   // Elimina los ficheros o directorios vacíos que se pasan como parámetro.
int deltree(char *tokens[], int ntokens, lista *listas);  // Elimina los ficheros o directorios vacíos de forma recursiva.

#endif //SHELL_C_COMANDOS_H
