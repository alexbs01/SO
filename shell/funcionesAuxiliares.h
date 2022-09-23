#ifndef SHELL_C_FUNCIONESAUXILIARES_H
#define SHELL_C_FUNCIONESAUXILIARES_H

#define MAX_LENGTH 255

#include <stdlib.h>
#include <stdio.h>
#include <string.h> // strdup para el historial, es un strcpy pero con malloc incluido

#include "comandos.h"
#include "lista.h"
#include "cabeceras.h"

int splitString(char *cadena, char *trozos[]);                  // Cuenta cuantos parámetros tiene un comando
int processInput(char *tokens[], int ntokens, list *lista);     // Procesa la entrada

int ayuda(char *tokens[], int ntokens, list *lista);            // Muestra la ayuda de cada comando

#endif //SHELL_C_FUNCIONESAUXILIARES_H