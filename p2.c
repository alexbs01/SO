/*
    Login: a.becerra
    Login: adrian.rego
    Nombre: Alejandro Becerra Suarez
    Nombre: Adrián Rego Criado
*/
#include "cabeceras.h"
//#include "funcionesAuxiliares.h"

#define MAX_INPUT_SIZE 1024
#define MAX_TOKENS 64

int main() {
    char input[MAX_INPUT_SIZE], *duplicateInput;
    char *tokens[MAX_TOKENS];
    int ntokens;
    int endShell = 0;
    lista historial = createEmptyList(); // Inicializamos una lista con cabecera
    lista listaMemoria = createEmptyList();
    structListas listas;
    listas.historial = historial;
    listas.listMemoryBlocks = listaMemoria;

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
    
    deleteList(&listas.listMemoryBlocks, free);
    deleteList(&listas.historial, free); // Liberamos la memoria dinámica
    return 0;
}

