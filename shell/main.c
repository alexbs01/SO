/*
    Login: a.becerra
    Login: adrian.rego
    Nombre: Alejandro Becerra Suarez
    Nombre: Adrián Rego Criado
*/

#include <stdio.h>
#include "funcionesAuxiliares.h"
#include "lista.h"

#define MAX_INPUT_SIZE 1024
#define MAX_TOKENS 64

int main() {
    char input[MAX_INPUT_SIZE], *duplicateInput;
    char *tokens[MAX_TOKENS];
    int ntokens;
    int endShell = 0;
    list historial = createEmptyList(); // Inicializamos una lista con cabecera
    insert(&historial, NULL);

    while(!endShell) {

        printf("\n> "); // Imprime el prompt

        fgets(input, MAX_INPUT_SIZE, stdin); // Recoge la línea que escribimos
        duplicateInput = strdup(input);
        insert(&historial, duplicateInput); // Duplicamos el string para incorporarlo al historial

        ntokens = splitString(input, tokens); // Se almancenan el número de tokens que hay en la cadena

        endShell = processInput(tokens, ntokens, &historial);
        if(isEmptyList(historial)) { // Si borramos el historial, volvemos a crearla y le insertamos la cabecera
            historial = createEmptyList();
            insert(&historial, NULL);
        }

        }
    deleteList(&historial); // LIberamos la memoria dinámica
    free(duplicateInput);
    return 0;
}
