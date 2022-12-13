/*
    Login: a.becerra
    Login: adrian.rego
    Nombre: Alejandro Becerra Suarez
    Nombre: Adrián Rego Criado
*/
#ifndef SHELL_CABECERAS_H
#define SHELL_CABECERAS_H

#define MAX_LENGTH 255
#define MAX_PATH 255

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
#include <time.h>
struct allocateMalloc {
    void *memoryAddress;
    long int size;
    char fecha[MAX_LENGTH];
};

struct allocateShared {
    void *memoryAddress;
    long int size;
    char fecha[MAX_LENGTH];
    int key;
};

struct allocateMmap {
    void *memoryAddress;
    long int size;
    char fecha[MAX_LENGTH];
    int descritor;
    char fich[MAX_LENGTH];
};

struct job {
    int pid;
    char *uName;
    //int priority;
    char *fecha;
    char *state;
    char *name;
    int out;
};

typedef struct listas {
    lista historial;
    lista allocateMalloc;
    lista allocateShared;
    lista allocateMmap;
    char **envp;
    lista job;
} structListas;

struct SEN {
    char *nombre;
    int senal;
};

#include <stdio.h>
#include <stdlib.h>

#include <errno.h> // Incluye la función: perror
#include <string.h>
#include <sys/utsname.h> // Utilizada por la función infosis
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <grp.h>
#include <stdio_ext.h>
#include <pwd.h>
#include <signal.h>
#include <unistd.h>
#define _GNU_SOURCE
//#include "funcionesAuxiliares.h"

#include "comandos.h"



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


