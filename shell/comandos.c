//
// Created by alexb on 09/09/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include "comandos.h"
#include "cabeceras.h"
#include "lista.h"
#include "funcionesAuxiliares.h"


int autores(char *tokens[], int ntokens, list *lista) {
    if(ntokens == 1) {
        if(strcmp(tokens[0], "-l") == 0) {
            printf("Login: a.becerra");
            printf("\nLogin: adrian.rego");
        } else if(strcmp(tokens[0], "-n") == 0) {
            printf("Nombre: Alejandro Becerra Suarez");
            printf("\nNombre: Adrián Rego Criado");
        } else {
            printf("Parámetro inválido.");
        }
    } else if (ntokens == 0) {
        printf("Login: a.becerra");
        printf("\nLogin: adrian.rego");
        printf("\nNombre: Alejandro Becerra Suarez");
        printf("\nNombre: Adrián Rego Criado");
    } else {
        printf("Número de parámetros incorrecto.");
    }

    return 0;
}

int pid(char *tokens[], int ntokens, list *lista) {
    pid_t pid = getpid();
    pid_t ppid = getppid();

    if(ntokens == 1) {
        if(strcmp(tokens[0], "-p") == 0) {
            printf("Pid parent process: %d", ppid);
        } else {
            printf("Parámetro inválido.");
        }
    } else if(ntokens == 0) {
        printf("Pid process: %d", pid);
    } else {
        printf("Número de parámetros incorrecto.");
    }
    return 0;
}

int carpeta(char *tokens[], int ntokens, list *lista) {
    char previousDirectory[MAX_LENGTH];
    char directory[MAX_LENGTH];
    char error[] = "No se pudo cambiar al directorio";

    if(ntokens == 1) {
        //char directory[MAX_LENGTH];
        getcwd(previousDirectory, sizeof(previousDirectory));
        chdir(tokens[0]);
        getcwd(directory, sizeof(directory));

        if(strcmp(previousDirectory, directory) == 0) {
            perror(error);
        }

        printf("%s", directory);

    } else if(ntokens == 0) {
        getcwd(directory, sizeof(directory));
        printf("%s", directory);
    } else {
        printf("Número de parámetros incorrecto.");
    }
    return 0;
}

int fecha(char *tokens[], int ntokens, list *lista) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    if(ntokens == 1) {
        if(strcmp(tokens[0], "-d") == 0) {
            printf("%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
        } else if(strcmp(tokens[0], "-h") == 0) {
            printf("%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
        } else {
            printf("Parámetro no encontrado.");
        }
    } else if (ntokens == 0) {
        printf("%02d/%02d/%d ", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
        printf("%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
    } else {
        printf("Número de parámetros incorrecto.");
    }

    return 0;
}

int hist(char *tokens[], int ntokens, list *lista) {
    int position = 1;

    if(ntokens == 1) {
        char *ptr;
        int numero = strtol(tokens[0], &ptr, 10) * -1;

        if(strcmp(tokens[0], "-c") == 0  ) {
            deleteList(lista);

        } else if(numero > 0 && numero < elementsNumber(*lista)) {

            int contador = 1;
            pos p;

            for(p = second(*lista); contador != numero+1; p = next(*lista, p)) {
                struct histData *info = get(*lista, p);
                printf("%d-> %s", contador, info->command);
                contador++;
            }

        }
        free(ptr);
    } else if(ntokens == 0) {
        for(pos p = second(*lista); !at_end(*lista, p); p = next(*lista, p)) {
            struct histData *info = get(*lista, p);
            printf("%d-> %s", position, info->command);
            position++;
        }

    } else {
        printf("Número incorrecto de parámetros aceptados por la función hist.");
    }

    return 0;
}

int comando(char *tokens[], int ntokens, list *lista) {

    if(ntokens == 1) {
        char *ptr;
        int numero = strtol(tokens[0], &ptr, 10) * -1;
        int contador = 1;

        if(numero > 0 && numero < elementsNumber(*lista)) {

            pos position;

            for(position = second(*lista); contador != numero; position = next(*lista, position)) {
                contador++;
            }
            struct histData *command = get(*lista, position);

            char *tokensHist[MAX_TOKENS];
            int numeroTokens = splitString(command->command, tokensHist);
            processInput(tokensHist, numeroTokens, lista);
            free(ptr);
        } else {
            printf("Se debe insertar un número mayor a 0 como parámetro");
        }
    } else {
        printf("El comando \"comando\" debe llevar una parámetro del tipo -N, donde N es un número\n"
               "Mira el historial con el comando \"hist\" para saber que comandos puedes ejecutar");
    }

    return 0;
}

int infosis(char *tokens[], int ntokens, list *lista) {

    char error[] = "Uname function fail";
    struct utsname systeminfo;

    if(!uname(&systeminfo)) {
        printf("%s (%s), OS: %s-%s-%s", systeminfo.nodename,
                                               systeminfo.machine,
                                               systeminfo.sysname,
                                               systeminfo.release,
                                               systeminfo.version);
    } else {
        perror(error);
    }

    return 0;
}



int fin(char *tokens[], int ntokens, list *lista) {
    bye(tokens, ntokens, lista);
}

int salir(char *tokens[], int ntokens, list *lista) {
    bye(tokens, ntokens, lista);
}

int bye(char *tokens[], int ntokens, list *lista) {
    return 1;
}