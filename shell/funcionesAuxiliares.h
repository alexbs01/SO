//
// Created by alexb on 09/09/2022.
//

#ifndef SHELL_C_FUNCIONESAUXILIARES_H
#define SHELL_C_FUNCIONESAUXILIARES_H

#define MAX_LENGTH 255
#include <stdlib.h>
#include <stdio.h>
#include <string.h> // strdup para el historial, es un strcpy pero con malloc incluido

#include "comandos.h"
#include "lista.h"
#include "cabeceras.h"

/*struct cmd {
    char *cmdName;
    int (*cmdFunction)(char *tokens[], int ntokens, list *lista);
    char *ayudaCmd[MAX_LENGTH];
};*/
struct cmd cmds[] = {
        {"autores", autores, "[-n] Imprime los nombres de los autores.\n[-l] Imprime los login de los autores.\n[] Imprime las dos cosas.\n"},
        {"pid", pid, "[] Imprime el pid del proceso que esta ejecutando el shell.\n[-p] Imprime el pid del proceso padre del shell.\n"},
        {"carpeta", carpeta, "[direct] Cambia el directorio de trabajo actual del shell para direct.\n[] Imprime el directorio de trabajo actual.\n"},
        {"fecha", fecha, "[-d] Imprime la fecha actual en formato: at DD/MM/YYYY.\n[-h] Imprime la fecha actual en formato: h:mm:ss.\n[] Imprime la fecha actual en los dos formatos.\n"},
        {"hist", hist, ""},
        {"comando", comando, ""},
        {"infosis", infosis, "Imprime información en la máquina que ejecuta el shell.\n"},
        {"ayuda", ayuda, "[] Imprime una lista de los comandos disponibles.\n[cmd] Imprime un poco de ayuda del comando cmd.\n"},
        {"fin", fin, "Acaba el funcionamiento del shell\n"},
        {"salir", salir, "Acaba el funcionamiento del shell\n"},
        {"bye", bye, "Acaba el funcionamiento del shell\n"},
        {NULL, NULL}
};



int splitString(char *cadena, char *trozos[]);
int processInput(char *tokens[], int ntokens, list *lista);

#endif //SHELL_C_FUNCIONESAUXILIARES_H