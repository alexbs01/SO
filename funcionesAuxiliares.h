/*
    Login: a.becerra
    Login: adrian.rego
    Nombre: Alejandro Becerra Suarez
    Nombre: Adrián Rego Criado
*/
#ifndef SHELL_C_FUNCIONESAUXILIARES_H
#define SHELL_C_FUNCIONESAUXILIARES_H

#define MAX_LENGTH 255

#include "cabeceras.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h> // strdup para el historial, es un strcpy pero con malloc incluido

#include "comandos.h"
#include "lista.h"

int splitString(char *cadena, char *trozos[]);                  // Cuenta cuantos parámetros tiene un comando
int processInput(char *tokens[], int ntokens, structListas *listas);     // Procesa la entrada

int ayuda(char *tokens[], int ntokens, structListas *listas);            // Muestra la ayuda de cada comando

// Esta dos funciones pertenecen a las funciones de ayuda dadas en la página web de SO
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
void * ObtenerMemoriaShmget (key_t clave, size_t tam, structListas *L);
void * ObtenerMemoriaShmgetShared (key_t clave, structListas *L);
void do_AllocateCreateshared (char *tr[], structListas L);

#endif //SHELL_C_FUNCIONESAUXILIARES_H