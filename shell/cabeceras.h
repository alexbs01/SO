#ifndef SHELL_CABECERAS_H
#define SHELL_CABECERAS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h> // Incluye la función: perror
#include <string.h>
#include <sys/utsname.h> // Utilizada por la función infosis
#include "funcionesAuxiliares.h"
#include "lista.h"

#define MAX_LENGTH 255

struct histData{ // Para obtener los commandos del historial
    char command[MAX_LENGTH];
};

#endif //SHELL_CABECERAS_H
