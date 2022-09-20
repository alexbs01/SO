//
// Created by alexb on 09/09/2022.
//

#include "comandos.h"

int autores(char *tokens[], int ntokens) {
    if(ntokens == 1) {
        if(strcmp(tokens[0], "-l") == 0) {
            printf("Login: a.becerra@udc.es");
            printf("\nLogin: adrian.rego@udc.es");
        } else if(strcmp(tokens[0], "-n") == 0) {
            printf("Nombre: Alejandro Becerra Suarez");
            printf("\nNombre: Adrián Rego Criado");
        } else {
            printf("Parámetro inválido.");
        }
    } else if (ntokens == 0) {
        printf("Login: a.becerra@udc.es");
        printf("\nLogin: adrian.rego@udc.es");
        printf("\nNombre: Alejandro Becerra Suarez");
        printf("\nNombre: Adrián Rego Criado");
    } else {
        printf("Número de parámetros incorrecto.");
    }

    return 0;
}

int pid(char *tokens[], int ntokens) {
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

int carpeta(char *tokens[], int ntokens) {
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

int fecha(char *tokens[], int ntokens) {
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

int hist(char *tokens[], int ntokens) {
    printf("hist");
    return 0;
}

int comando(char *tokens[], int ntokens) {
    printf("comando");
    return 0;
}

int infosis(char *tokens[], int ntokens) {
    printf("infosis");
    return 0;
}

int ayuda(char *tokens[], int ntokens) {
    printf("ayuda");
    return 0;
}

int fin(char *tokens[], int ntokens) {
    bye(tokens, ntokens);
}

int salir(char *tokens[], int ntokens) {
    bye(tokens, ntokens);
}

int bye(char *tokens[], int ntokens) {
    return 1;
}