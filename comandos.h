/*
    Login: a.becerra
    Login: adrian.rego
    Nombre: Alejandro Becerra Suarez
    Nombre: Adrián Rego Criado
*/
#ifndef SHELL_C_COMANDOS_H
#define SHELL_C_COMANDOS_H

#include "cabeceras.h"
#include "funcionesAuxiliares.h"
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h> // Para el comando <list>
#include <grp.h>    // Para el comando <list>
#include <pwd.h>    // Para el comando <list>
#include "lista.h"

#define MAX_LENGTH 255
#define MAX_INPUT_SIZE 1024
#define MAX_TOKENS 64

int autores(char *tokens[], int ntokens, structListas *listas);  // Imprime los nombres, los login o ambas.
int pid(char *tokens[], int ntokens, structListas *listas);      // Muestra el pid o el pid padre.
int carpeta(char *tokens[], int ntokens, structListas *listas);  // Muestra la carpeta y permite desplazarse a través de los directorios.
int fecha(char *tokens[], int ntokens, structListas *listas);    // Imprime la fecha, la hora o ambas.
int hist(char *tokens[], int ntokens, structListas *listas);     // Muestra el historial de comando usados.
int comando(char *tokens[], int ntokens, structListas *listas);  // Permite ejecutar un comando usado con anterioridad.
int infosis(char *tokens[], int ntokens, structListas *listas);  // Enseña la información del sistema: SO, arquitectura, nombre del PC...
int fin(char *tokens[], int ntokens, structListas *listas);      // Fin, salir y bye, finalizan la ejecución del programa.
int salir(char *tokens[], int ntokens, structListas *listas);
int bye(char *tokens[], int ntokens, structListas *listas);

int create(char *tokens[], int ntokens, structListas *listas);   // Crea una carpeta o un fichero.
int stats(char *tokens[], int ntokens, structListas *listas);    // Retorna datos del archivo
int list(char *tokens[], int ntokens, structListas *listas);     // Retorna los datos de los archivos del directorio
int delete(char *tokens[], int ntokens, structListas *listas);   // Elimina los ficheros o directorios vacíos que se pasan como parámetro.
int deltree(char *tokens[], int ntokens, structListas *listas);  // Elimina los ficheros o directorios de forma recursiva.

int allocate(char *tokens[], int ntokens, structListas *listas); // Reserva memoria
int deallocate(char *tokens[], int ntokens, structListas *listas); // Libera memoria
int io(char *tokens[], int ntokens, structListas *listas);       // Lee o escribe en una dirección de memoria
int memdump(char *tokens[], int ntokens, structListas *listas);  // Vuelva una dirección de memoria y muestra su contenido
int memfill(char *tokens[], int ntokens, structListas *listas);  // Rellena una cantidad de memoria con un byte indicado
int memory(char *tokens[], int ntokens, structListas *listas);   // Muestra direcciones de memoria
int recurse(char *tokens[], int ntokens, structListas *listas);  // Muestra una las direcciones de memoria de una función recursiva

int priority(char *tokens[], int ntokens, structListas *listas); // Muestra y cambia la prioridad de un proceso
int showvar(char *tokens[], int ntokens, structListas *listas);  // Muestras las variables de entorno
int changevar(char *tokens[], int ntokens, structListas *listas);// Cambia una varible de entorno de tres formas distintas
int showenv(char *tokens[], int ntokens, structListas *listas);  // Muestra el entorno o las variables de entorno
int forkA(char *tokens[], int ntokens, structListas *listas);    // Hace fork del shell
int execute(char *tokens[], int ntokens, structListas *listas);  // Ejecuta un programa, con @N, asigna una prioridad N
int listjobs(char *tokens[], int ntokens, structListas *listas); // Lista los procesos en ejecución
int deljobs(char *tokens[], int ntokens, structListas *listas);  // Elimina de la lista de procesos
int job(char *tokens[], int ntokens, structListas *listas);      // Lista procesos y permite pasar a primer plano los de background
#endif //SHELL_C_COMANDOS_H
