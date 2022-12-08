/*
    Login: a.becerra
    Login: adrian.rego
    Nombre: Alejandro Becerra Suarez
    Nombre: Adrián Rego Criado
*/
#ifndef SHELL_C_FUNCIONESAUXILIARES_H
#define SHELL_C_FUNCIONESAUXILIARES_H

#define MAX_LENGTH 255
#define MAXVAR 200

#include "cabeceras.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h> // strdup para el historial, es un strcpy pero con malloc incluido
#include <stdio.h>
#include "lista.h"
#include "comandos.h"
#include "lista.h"

int splitString(char *cadena, char *trozos[]);                  // Cuenta cuantos parámetros tiene un comando
int processInput(char *tokens[], int ntokens, structListas *listas);     // Procesa la entrada

int ayuda(char *tokens[], int ntokens, structListas *listas);            // Muestra la ayuda de cada comando

// Estas dos funciones pertenecen a las funciones de ayuda dadas en la página web de SO
char LetraTF (mode_t m);
char * ConvierteModo2 (mode_t m);

// Funciones de la práctica 1
/*aaa*/
off_t tamanoFichero(char *file); // Retorna el tamaño de un fichero
int printStatAndList(char *tokens, SStatListCommand flags); // Imprime la información de un archivo
int isDirectory(char *tokens); // Comprueba que sea un directorio
int delete_item(char *path); // Borra recursivamente, hecha a partir del código de París
int listarCarpeta(char *tokens, SStatListCommand flags, int ntokens); // Lista la carpeta
int listaArbolCarpetas(char *path, SStatListCommand flags); // Lista carpetas de forma recursiva, hecha a partir del código de París

void mostrarListaMalloc(structListas L);
void mostrarListaShared(structListas L);
void mostrarListaMmap(structListas L);

void do_AllocateMalloc(char *tokens[], structListas *L);
void do_AllocateCreateshared (char *tr[], structListas L);
void do_AllocateMmap(char *arg[], structListas L);

void * ObtenerMemoriaShmget (key_t clave, size_t tam, structListas *L);
void * MapearFichero (char * fichero, int protection, structListas *L);

void deallocateMalloc(structListas L, long int tam);
void deallocateShared(structListas L, key_t key);
void do_DeallocateDelkey (char *args[]);
void deallocateMmap(structListas L, char *args[]);
void deallocateAddr(structListas L, void *n);

ssize_t LeerFichero (char *f, void *p, size_t cont);
void do_I_O_read (char *ar[]);
ssize_t EscribirFichero (char *f, void *p, size_t cont,int overwrite);
void do_I_O_write (char *ar[]);

void LlenarMemoria (void *p, size_t cont, unsigned char byte);
void Do_pmap (void);
void Recursiva (int n);
void liberarMalloc(void *addr);
void liberarMmap(void *addr);
void liberarShared(void *addr);

int BuscarVariable (char * var, char *e[]);
int CambiarVariable(char * var, char * valor, char *e[]);
#endif //SHELL_C_FUNCIONESAUXILIARES_H