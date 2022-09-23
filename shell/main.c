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
    list historial = createEmptyList();
    insert(&historial, NULL);

    while(!endShell) {
        printf("\n> ");

        fgets(input, MAX_INPUT_SIZE, stdin);
        duplicateInput = strdup(input);
        insert(&historial, duplicateInput);
        free(duplicateInput);
        ntokens = splitString(input, tokens);

        endShell = processInput(tokens, ntokens, &historial);
        if(isEmptyList(historial)) {
            historial = createEmptyList();
            insert(&historial, NULL);
        }
        //printf("\n%s ", input);

        }
    deleteList(&historial);

    return 0;
}
