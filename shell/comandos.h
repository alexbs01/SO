#ifndef SHELL_C_COMANDOS_H
#define SHELL_C_COMANDOS_H

#include "cabeceras.h"

#define MAX_LENGTH 255
#define MAX_INPUT_SIZE 1024
#define MAX_TOKENS 64

int autores(char *tokens[], int ntokens, list *lista);  // Imprime los nombres, los login o ambas.
int pid(char *tokens[], int ntokens, list *lista);      // Muestra el pid o el pid padre
int carpeta(char *tokens[], int ntokens, list *lista);  // Muestra la carpeta y permite desplazarse a través de los directorios
int fecha(char *tokens[], int ntokens, list *lista);    // Imprime la fecha, la hora o ambas
int hist(char *tokens[], int ntokens, list *lista);     // Muestra el historial de comando usados
int comando(char *tokens[], int ntokens, list *lista);  // Permite ejecutar un comando usado con anterioridad
int infosis(char *tokens[], int ntokens, list *lista);  // Enseña la información del sistema: SO, arquitectura, nombre del PC...
int fin(char *tokens[], int ntokens, list *lista);      // Fin, salir y bye, finalizan la ejecución del programa
int salir(char *tokens[], int ntokens, list *lista);
int bye(char *tokens[], int ntokens, list *lista);

#endif //SHELL_C_COMANDOS_H
