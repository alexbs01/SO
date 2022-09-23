//
// Created by alexb on 09/09/2022.
//

#ifndef SHELL_C_COMANDOS_H
#define SHELL_C_COMANDOS_H

#include "cabeceras.h"

#define MAX_LENGTH 255
#define MAX_INPUT_SIZE 1024
#define MAX_TOKENS 64

int autores(char *tokens[], int ntokens, list *lista);
int pid(char *tokens[], int ntokens, list *lista);
int carpeta(char *tokens[], int ntokens, list *lista);
int fecha(char *tokens[], int ntokens, list *lista);
int hist(char *tokens[], int ntokens, list *lista);
int comando(char *tokens[], int ntokens, list *lista);
int infosis(char *tokens[], int ntokens, list *lista);
int fin(char *tokens[], int ntokens, list *lista);
int salir(char *tokens[], int ntokens, list *lista);
int bye(char *tokens[], int ntokens, list *lista);

#endif //SHELL_C_COMANDOS_H
