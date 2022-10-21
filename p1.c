/*
    Login: a.becerra
    Login: adrian.rego
    Nombre: Alejandro Becerra Suarez
    Nombre: Adrián Rego Criado
*/
#include "cabeceras.h"

#define MAX_INPUT_SIZE 1024
#define MAX_TOKENS 64

int main() {
    char input[MAX_INPUT_SIZE], duplicateInput[MAX_LENGTH];
    char *tokens[MAX_TOKENS];
    int ntokens;
    int endShell = 0;
    lista historial = createEmptyList(); // Inicializamos una lista con cabecera
    insert(&historial, NULL);

    while(endShell != 1) {

        printf("\n> "); // Imprime el prompt

        fgets(input, MAX_INPUT_SIZE, stdin); // Recoge la línea que escribimos

        if(input[0] == '\n') { // Evita que si no se introduce nada por el terminal, se corte la ejecución del programa
            continue;
        }

        strcpy(duplicateInput, input);
        insert(&historial, duplicateInput); // Duplicamos el string para incorporarlo al historial

        ntokens = splitString(input, tokens); // Se almacenan el número de tokens que hay en la cadena

        endShell = processInput(tokens, ntokens, &historial);
        if(isEmptyList(historial)) { // Si borramos el historial, volvemos a crearla y le insertamos la cabecera
            historial = createEmptyList();
            insert(&historial, NULL);
        }

    }

    deleteList(&historial); // Liberamos la memoria dinámica
    return 0;
}

