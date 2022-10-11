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
int processInput(char *tokens[], int ntokens, lista *lista);     // Procesa la entrada

int ayuda(char *tokens[], int ntokens, lista *lista);            // Muestra la ayuda de cada comando

// Esta dos funciones pertenecen a las funciones de ayuda dadas en la página web de SO
char LetraTF (mode_t m);
char * ConvierteModo2 (mode_t m);

int printStat(char tokens, SStatCommand *flags);

#endif //SHELL_C_FUNCIONESAUXILIARES_H