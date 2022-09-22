//
// Created by alexb on 09/09/2022.
//

#include <stdio.h>
#include "funcionesAuxiliares.h"
#include "lista.h"
#include "cabeceras.h"

int splitString(char *cadena, char *trozos[]) {
    int i=1;
    if((trozos[0] = strtok(cadena, " \n\t")) == NULL) {
        return 0;
    }

    while((trozos[i] = strtok(NULL, " \n\t")) != NULL) {
        i++;
    }
    return i;
}

/*struct cmd cmds[] = {
        {"autores", autores, "[-n] Imprime los nombres de los autores.\n[-l] Imprime los login de los autores.\n[] Imprime las dos cosas.\n"},
        {"pid", pid, "[] Imprime el pid del proceso que esta ejecutando el shell.\n[-p] Imprime el pid del proceso padre del shell.\n"},
        {"carpeta", carpeta, "[direct] Cambia el directorio de trabajo actual del shell para direct.\n[] Imprime el directorio de trabajo actual.\n"},
        {"fecha", fecha, "[-d] Imprime la fecha actual en formato: at DD/MM/YYYY.\n[-h] Imprime la fecha actual en formato: h:mm:ss.\n[] Imprime la fecha actual en los dos formatos.\n"},
        {"hist", hist, ""},
        {"comando", comando, ""},
        {"infosis", infosis, "Imprime información en la máquina que ejecuta el shell.\n"},
        {"ayuda", ayuda, "[] Imprime una lista de los comandos disponibles.\n[cmd] Imprime un poco de ayuda del comando cmd.\n"},
        {"fin", fin, ""},
        {"salir", salir, ""},
        {"bye", bye, ""},
        {NULL, NULL}
};*/

int processInput(char *tokens[], int ntokens, list *lista) {
    int exit = 0;
    for(int i = 0; cmds[i].cmdName != NULL; i++) {
        if(strcmp(tokens[0], cmds[i].cmdName) == 0) {
            exit = cmds[i].cmdFunction(tokens + 1, ntokens - 1, lista);
            return exit;
        }
    }

    printf("Comando no encontrado");
    return exit;
}

