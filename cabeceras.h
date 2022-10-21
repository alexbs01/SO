/*
    Login: a.becerra
    Login: adrian.rego
    Nombre: Alejandro Becerra Suarez
    Nombre: Adrián Rego Criado
*/
#ifndef SHELL_CABECERAS_H
#define SHELL_CABECERAS_H

#include <stdbool.h>
typedef struct statCommand {
    bool longFlag;
    bool linkFlag;
    bool accFlag;
    bool recaFlag;
    bool recbFlag;
    bool hidFlag;
} SStatListCommand;
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h> // Incluye la función: perror
#include <string.h>
#include <sys/utsname.h> // Utilizada por la función infosis
#include <sys/stat.h>
#include <dirent.h>
//#include "funcionesAuxiliares.h"

#include "comandos.h"

#define MAX_LENGTH 255
#define MAX_PATH 255

struct histData{ // Para obtener los commandos del historial
    char command[MAX_LENGTH];
};

// Código de París
/*
int delete_item(char *path) {
    struct stat st;

    if(lstat(path, &st) == -1) {
        printf("Could not access %s: %s\n", path, strerror(errno));
        return 0;
    }

    if((st.st_mode & S_IFMT) == S_IFDIR) { // path es un directorio
        DIR *d;
        struct dirent *ent;

        if((d = opendir(path)) == NULL) {
            printf("Could not open %s: %s\n", path, strerror(errno));
            return 0;
        }

        while((ent = readdir(d)) != NULL) {
            char new_path[MAX_PATH];

            if(strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
                continue;

            sprintf(new_path, "%s/%s", path, ent->d_name);

            delete_item(new_path);
        }
        closedir(d);
    }

    if(remove(path) == -1) {
        printf("Could not delete %s: %s\n", path, strerror(errno));
    }

    printf("Borrar %s\n", path);
}



for(int i = 1; tokens[i] != NULL; i++) {
    delete_item(tokens[i]);
}*/

#endif //SHELL_CABECERAS_H


