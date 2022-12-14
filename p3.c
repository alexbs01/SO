/*
    Login: a.becerra
    Login: adrian.rego
    Nombre: Alejandro Becerra Suarez
    Nombre: Adrián Rego Criado
*/
#include "cabeceras.h"
#include "funcionesAuxiliares.h"

#define MAX_INPUT_SIZE 1024
#define MAX_TOKENS 64

int main(int argc, char *argv[], char *envp[]) {
    char input[MAX_INPUT_SIZE], *duplicateInput;
    char *tokens[MAX_TOKENS];
    int ntokens;
    int endShell = 0;
    lista historial = createEmptyList(); // Inicializamos una lista con cabecera
    lista allocateMalloc = createEmptyList();
    lista allocateShared = createEmptyList();
    lista allocateMmap = createEmptyList();
    lista job = createEmptyList();
    structListas listas = {historial, allocateMalloc, allocateShared, allocateMmap, envp, job};

    while(endShell != 1) {

        printf("\n> "); // Imprime el prompt

        fgets(input, MAX_INPUT_SIZE, stdin); // Recoge la línea que escribimos

        if(input[0] == '\n') { // Evita que si no se introduce nada por el terminal, se corte la ejecución del programa
            continue;
        }

        duplicateInput = strdup(input);
        insert(&listas.historial, duplicateInput); // Duplicamos el string para incorporarlo al historial

        ntokens = splitString(input, tokens); // Se almacenan el número de tokens que hay en la cadena

        endShell = processInput(tokens, ntokens, &listas);
        if(endShell == 2) { // Si borramos el historial se retornará un 2, y entonces se creará un nuevo historial
            listas.historial = createEmptyList();
        }

    }

    // Liberamos la memoria de las listas antes de finalizar el programa
    deleteList(&listas.allocateMalloc, liberarMalloc);
    deleteList(&listas.allocateShared, liberarShared);
    deleteList(&listas.allocateMmap, liberarMmap);
    deleteList(&listas.historial, free);
    deleteList(&listas.job, free);
    return 0;
}
