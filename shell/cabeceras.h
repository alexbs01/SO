//
// Created by alexbs01 on 22/09/22.
//

#ifndef SHELL_CABECERAS_H
#define SHELL_CABECERAS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h> // Perror
#include <string.h>
#include <sys/utsname.h> //infosis
#include "funcionesAuxiliares.h"
#include "lista.h"

#define MAX_LENGTH 255

struct histData{ //data for history list
    char command[MAX_LENGTH];
};

#endif //SHELL_CABECERAS_H
