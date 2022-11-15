/*
    Login: a.becerra
    Login: adrian.rego
    Nombre: Alejandro Becerra Suarez
    Nombre: Adrián Rego Criado
*/
#include <stdio.h>
#include <stdlib.h>
#include "comandos.h"

int global1 = 1, global2 = 2, global3 = 3;

int autores(char *tokens[], int ntokens, structListas *listas) {
    if(ntokens == 1) {                                          // Miramos si autores viene acompañado de [-l] o [-n]
        if(strcmp(tokens[0], "-l") == 0) {
            printf("Login: a.becerra");                 // En caso de [-l] damos por salida los logins de los autores
            printf("\nLogin: adrian.rego");
        } else if(strcmp(tokens[0], "-n") == 0) {
            printf("Nombre: Alejandro Becerra Suarez"); // En caso de [-n] damos por salida los nombres de los autores
            printf("\nNombre: Adrián Rego Criado");
        } else {
            printf("Parámetro inválido.");              // Si han puesto otra cosa entre los corchetes, se mostrará que ese comando no existe
        }
    } else if (ntokens == 0) {                                // Si autores no viene acompañado de [-l] o [-n] se
        printf("Login: a.becerra");                    // mostrarán tanto los nombres como los login pro salida
        printf("\nLogin: adrian.rego");
        printf("\nNombre: Alejandro Becerra Suarez");
        printf("\nNombre: Adrián Rego Criado");
    } else {
        printf("Número de parámetros incorrecto.");     //Si han puesto mas corchetes que uno, se mostrará que ese comando no existe
    }

    return 0;
}

int pid(char *tokens[], int ntokens, structListas *listas) {
    pid_t pid = getpid();
    pid_t ppid = getppid();

    if(ntokens == 1) {  //Miramos si pid viene acompañado de [-p] o no
        if(strcmp(tokens[0], "-p") == 0) {
            printf("Pid parent process: %d", ppid);  //Si hay [-p] mostramos el ppid
        } else {
            printf("Parámetro inválido.");  //Si han puesto otra cosa entre los corchetes, se mostrará que ese comando no existe
        }
    } else if(ntokens == 0) {  //Si pid no viene acompañado de otro comando entre corchetes mostramos el pid
        printf("Pid process: %d", pid);
    } else {
        printf("Número de parámetros incorrecto.");  //Si han puesto mas corchetes que uno, se mostrará que ese comando no existe
    }
    return 0;
}

int carpeta(char *tokens[], int ntokens, structListas *listas) {
    char previousDirectory[MAX_LENGTH]; // Creamos una variable con un tamaño máximo para el directorio actual y el previo
    char directory[MAX_LENGTH];
    char error[] = "No se pudo cambiar al directorio"; // Mensaje de error por si no puede cambiar de directorio

    if(ntokens == 1) {  // Miramos si carpeta viene acompañado de una [ruta] o no.

        getcwd(previousDirectory, sizeof(previousDirectory));
        chdir(tokens[0]);                           // Si tiene parámetros nos cambiamos de directorio con chdir
        getcwd(directory, sizeof(directory));

        if(strcmp(previousDirectory, directory) == 0) { // Si el directorio actual es idéntico al previo, es que no
            perror(error);                           // se puedo cambiar, por lo que hubo un error
        }

        printf("%s", directory);

    } else if(ntokens == 0) { // Si no tiene parámetros muestra el actual
        getcwd(directory, sizeof(directory));
        printf("%s", directory);
    } else {
        printf("Número de parámetros incorrecto.");  //Si han puesto mas corchetes que uno, se mostrará que ese comando no existe
    }
    return 0;
}

int fecha(char *tokens[], int ntokens, structListas *listas) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    if(ntokens == 1) {                                                          // Miramos si fecha viene acompañado de un comando entre [] o no
        if(strcmp(tokens[0], "-d") == 0) {                                      // Si hay [-d] mostramos la fecha en forma de DD/MM/YYYY
            printf("%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

        } else if(strcmp(tokens[0], "-h") == 0) {                               // Si hay [-h] mostramos la fecha en forma de hh:mm:ss
            printf("%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);

        } else {
            printf("Parámetro no encontrado.");                //Si han puesto otra cosa entre los corchetes, se mostrará que ese comando no existe
        }
    } else if (ntokens == 0) {           //Si fecha no viene acompañado de [-d] o [-h] se mostrará la fecha con los dos formatos DD/MM/YYYY y hh:mm:ss
        printf("%02d/%02d/%d ", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
        printf("%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);

    } else {
        printf("Número de parámetros incorrecto.");  //Si han puesto mas comandos entre corchetes que uno, se mostrará que ese comando no existe

    }

    return 0;
}

int hist(char *tokens[], int ntokens, structListas *listas) {
    int position = 1;

    if(ntokens == 1) {  //Miramos si hist viene acompañado de un comando entre [] o no

        int numero = atoi(tokens[0]) * -1; // Sacamos el número introducido y lo volvemos positivo

        if(strcmp(tokens[0], "-c") == 0  ) {    //Si hay [-c] se borrará la lista que guarda el historial de comandos.
            deleteList(&listas->historial, free);
            return 2;
        } else if(numero > 0 && numero < elementsNumber(listas->historial)) { // Comprobamos que el número esté dentro del número de elementos del historial

            int contador = 1;
            pos p;

            for(p = first(listas->historial); contador != numero+1; p = next(listas->historial, p)) {
                struct histData *info = get(listas->historial, p);
                printf("%d-> %s", contador, info->command); // Mostramos los N primeros comandos
                contador++;
            }

        }

    } else if(ntokens == 0) { // Si hist no viene acompañado de [-c] o [-N] se mostrará por pantalla toda la lista de comandos usada.
        for(pos p = first(listas->historial); !at_end(listas->historial, p); p = next(listas->historial, p)) {
            struct histData *info = get(listas->historial, p);
            printf("%d-> %s", position, info->command); // Mostramos los comandos desde el primero al último
            position++;
        }

    } else {
        printf("Número incorrecto de parámetros aceptados por la función hist.");  //Si han puesto mas comandos entre corchetes que uno, se mostrara que ese comando no existe.
    }

    return 0;
}

int comando(char *tokens[], int ntokens, structListas *listas) {

    if(ntokens == 1) {

        int numero = atoi(tokens[0]) * -1; // El número introducido lo volvemos positivo
        int contador = 1;

        if(numero > 0 && numero < elementsNumber(listas->historial)) {
            pos position;

            for(position = first(listas->historial); contador != numero; position = next(listas->historial, position)) {
                contador++; // Guardamos en position, el comando que estamos buscando
            }

            struct histData *command = get(listas->historial, position);
            char *tokensHist[MAX_TOKENS];
            int numeroTokens = splitString(command->command, tokensHist);
            processInput(tokensHist, numeroTokens, listas); // Con el comando encontrado, los procesamos para ejecutarlo

        } else {
            printf("Se debe insertar un número precedido de una guión y que exista dentro del historial");
        }
    } else {
        printf("El comando \"comando\" debe llevar una parámetro del tipo -N, donde N es un número\n"
               "Mira el historial con el comando \"hist\" para saber que comandos puedes ejecutar");
    }

    return 0;
}

int infosis(char *tokens[], int ntokens, structListas *listas) {
    char error[] = "Uname function fail";   // Mensaje que mostraremos de salida por si la función uname falla
    struct utsname systeminfo;              // Gracias a la librería <sys/utsname.h> creamos una variable de
                                            // tiempo struct utsname donde se guardan los datos del dispositivo

    if(!uname(&systeminfo)) {          // Mostramos todos los datos almacenados en el struct
        printf("%s (%s), OS: %s-%s-%s", systeminfo.nodename,
                                               systeminfo.machine,
                                               systeminfo.sysname,
                                               systeminfo.release,
                                               systeminfo.version);
    } else {
        perror(error);                     // Si no funciona la función uname mostramos por salida un mensaje de error
    }

    return 0;
}



int fin(char *tokens[], int ntokens, structListas *listas) { // Función para acabar la ejecución del programa, hace que se devuelva 1
    return 1;
}

int salir(char *tokens[], int ntokens, structListas *listas) { // Función para acabar la ejecución del programa, hace que se devuelva 1
    return 1;
}

int bye(char *tokens[], int ntokens, structListas *listas) { // Función para acabar la ejecución del programa, hace que se devuelva 1
    return 1;
}

int create(char *tokens[], int ntokens, structListas *listas) {
    int errorNumber;

    if(ntokens == 1) {
        errorNumber = mkdir(tokens[0], 0771); // Se crea la carpeta con permisos rwxrwx--x, y se guarda el número de error

        if(errorNumber == -1) { // Si hay número de error es que no se pudo crear la carpeta
            printf("No se pudo crear %s: %s", tokens[0], strerror(errno));

        } else {
            printf("Se creo la carpeta: %s", tokens[0]);

        }

    } else if(ntokens == 2) {
        if(strcmp(tokens[0], "-f") == 0) {
            fopen(tokens[1], "wb"); // Creamos el fichero con el nombre de tokens[1]
            printf("Se creo el archivo: %s", tokens[1]);

        } else {
            printf("Parámetro incorrecto.");
        }

    } else {
        printf("Numero de parámetros incorrecto.");
    }
    return 0;
}

int stats(char *tokens[], int ntokens, structListas *listas) {
    SStatListCommand flags = {false, false, false, false, false, false};
    int numberFlags = 0;

    if(ntokens != 0) {
        for(int i = 0; i < ntokens; i++) {
            if(strcmp(tokens[i], "-long") == 0) {
                flags.longFlag = true;
                numberFlags++;
            } else if(strcmp(tokens[i], "-link") == 0) {
                flags.linkFlag = true;
                numberFlags++;
            } else if(strcmp(tokens[i], "-acc") == 0) {
                flags.accFlag = true;
                numberFlags++;
            }
        }

        if(flags.longFlag) {
            printf("   Date\t\tNº of hardlinks\t  Inodes    \tUser ID   \tGroup ID\tPermissions\tTotal size\tFile\n");
        }

        for(int i = numberFlags - 1; i < ntokens; i++) {
            printStatAndList(tokens[i], flags);
        }

    } else {
        carpeta(NULL, 0, NULL); // Si solo se pone stat sin ningún parámetro, muestra el directorio actual

    }

    return 0;
}


int list(char *tokens[], int ntokens, structListas *listas) {
    SStatListCommand flags = {false, false, false, false, false, false};
    int numberFlags = 0;

    if(ntokens != 0) {
        for (int i = 0; i < ntokens; i++) {
            if(strcmp(tokens[i], "-long") == 0) {
                flags.longFlag = true;
                numberFlags++;

            } else if (strcmp(tokens[i], "-link") == 0) {
                flags.linkFlag = true;
                numberFlags++;

            } else if (strcmp(tokens[i], "-acc") == 0) {
                flags.accFlag = true;
                numberFlags++;

            } else if (strcmp(tokens[i], "-reca") == 0) {
                flags.recaFlag = true;
                numberFlags++;

            } else if (strcmp(tokens[i], "-recb") == 0) {
                flags.recbFlag = true;
                numberFlags++;

            } else if (strcmp(tokens[i], "-hid") == 0) {
                flags.hidFlag = true;
                numberFlags++;
            }
        }

        // Imprime del formato largo si se escribe el parámetro correspondiente
        if(flags.longFlag) {
            printf("   Date\t\tNº of hardlinks\t  Inodes    \tUser ID   \tGroup ID\tPermissions\tTotal size\tFile\n");
        }

        if(!(flags.recaFlag || flags.recbFlag)) {
            for(int i = 0 + numberFlags; i < ntokens; i++) {
                listarCarpeta(tokens[i], flags, ntokens);
            }

        } else {
            for(int i = 0 + numberFlags; i < ntokens; i++) {
                if(flags.recaFlag) {
                    listarCarpeta(tokens[i], flags, ntokens);
                }
                listaArbolCarpetas(tokens[i], flags);
                if(flags.recbFlag && !flags.recaFlag) {
                    listarCarpeta(tokens[i], flags, ntokens);
                }

            }

        }

    } else {
        carpeta(NULL, 0, NULL); // Si solo se pone list sin ningún parámetro, muestra el directorio actual
    }

    return 0;
}


int delete(char *tokens[], int ntokens, structListas *listas) {
    char error[] = "No se pudo borrar el fichero";
    int i = 0;

    if(ntokens != 0) {
        do {
            if(remove(tokens[i]) == 0) {
                printf("Archivo %s eliminado\n", tokens[i]);
            } else {
                perror(error);
                return -1;
            }
            i++;
        } while(i < ntokens);
    } else {
        carpeta(NULL, 0, NULL);
    }
    return 0;
}

int deltree(char *tokens[], int ntokens, structListas *listas) {
    char error[] = "No se puede borrar";

    if(ntokens != 0) {
        for(int i = 0; i < ntokens; i++) {
            if(isDirectory(tokens[i])) {
                if(delete_item(tokens[i]) == -1 && remove(tokens[i])) {
                    perror(error);
                } else if(remove(tokens[i])) {
                    perror(error);
                }
            }

        }
    } else { //muestra el directorio actual
        carpeta(NULL,0,NULL);
    }

    return 0;
}

int allocate(char *tokens[], int ntokens, structListas *listas) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    void *memoryAddress;
    char typeOfAllocation[MAX_LENGTH];


    if(ntokens != 0) {
        if(strcmp(tokens[0], "-malloc") == 0) {
            if(ntokens == 2) {
                struct allocateMalloc *LMB = malloc(sizeof(struct allocateMalloc));
                int size = atoi(tokens[1]);
                memoryAddress = malloc(*tokens[1]);
                LMB->memoryAddress = memoryAddress;
                LMB->size = size;
                LMB->tm = localtime(&t);

                printf("Asignados %d bytes en %p", size, LMB->memoryAddress);

                insert(&listas->allocateMalloc, LMB);
            } else if(ntokens == 1) {
                printf("*** Lista de bloques asignados con malloc para el proceso %d", getpid());
                mostrarListaMalloc(*listas);
            }

        } else if(strcmp(tokens[0], "-shared") == 0) {
            if(ntokens == 2) {
                //struct allocateShared *LMB = malloc(sizeof(struct allocateShared));
                key_t key = atoi(tokens[1]);
                //void *tamano = get(listas->allocateShared, find(listas->allocateShared, tokens[1]));
                void * ptr = ObtenerMemoriaShmget(key, 0, listas);
                printf("Memoria compartida de clave %d en %p", key, ptr);

            } else if(ntokens == 1) {
                printf("*** Lista de bloques asignados con shared para el proceso %d", getpid());
                mostrarListaShared(*listas);
            }

        } else if(strcmp(tokens[0], "-createshared") == 0) {
            if(ntokens == 3) {
                int key = atoi(tokens[1]);
                long int size = atoi(tokens[2]);
                //ObtenerMemoriaShmget(key, size, listas);
                do_AllocateCreateshared(tokens, *listas);

            } else if(ntokens == 1) {
                printf("*** Lista de bloques asignados con shared para el proceso %d", getpid());
                mostrarListaShared(*listas);
            }

        } else if(strcmp(tokens[0], "-mmap") == 0) {
            if(ntokens == 2) {
                do_AllocateMmap(tokens, *listas);

            } else if(ntokens == 1) {
                printf("*** Lista de bloques asignados con mmap para el proceso %d", getpid());
                mostrarListaMmap(*listas);
            }
        } else {
            printf("Uso: allocate [-malloc size | -shared | -createshared | -mmap] ...");
        }
    } else {
        printf("*** Lista de bloques asignados para el proceso %d", getpid());
        mostrarListaMalloc(*listas);
        mostrarListaShared(*listas);
        mostrarListaMmap(*listas);
    }

    return 0;
}
int deallocate(char *tokens[], int ntokens, structListas *listas) {
    if (ntokens != 0) {
        if (strcmp(tokens[0], "-malloc") == 0) {
            if (ntokens == 2) {
                deallocateMalloc(*listas, (long int) atoi(tokens[1]));

            } else if (ntokens == 1) {
                printf("*** Lista de bloques asignados con malloc para el proceso %d", getpid());
                mostrarListaMalloc(*listas);
            }

        } else if (strcmp(tokens[0], "-shared") == 0) {
            if (ntokens == 2) {
                deallocateShared(*listas, (key_t) atoi(tokens[1]));

            } else if (ntokens == 1) {
                printf("*** Lista de bloques asignados con shared para el proceso %d", getpid());
                mostrarListaShared(*listas);
            }

        } else if (strcmp(tokens[0], "-delkey") == 0) {
            if (ntokens == 2) {
                do_DeallocateDelkey (tokens);

            } else if (ntokens == 1) {
                printf("*** Lista de bloques asignados con shared para el proceso %d", getpid());
                mostrarListaShared(*listas);
            }

        } else if (strcmp(tokens[0], "-mmap") == 0) {
            if (ntokens == 2) {
                //// Liberar Mmap

            } else if (ntokens == 1) {
                printf("*** Lista de bloques asignados con mmap para el proceso %d", getpid());
                mostrarListaMmap(*listas);
            }

        } else {
            printf("[] Desasigna un bloque de memoria. \n [-malloc tam] Desasigna un bloque malloc de tamano tam. \n [-shared cl] Desasigna (desmapea) el bloque de memoria compartida de clave cl. \n [-delkey cl] Elimina del sistema (sin desmapear) la clave de memoria cl. \n [-nmap fich] Desmapea el fichero mapeado fich. \n [-addr] Desasigna el bloque de memoria en la dirección adrr");
        }
    } else {
        printf("*** Lista de bloques asignados para el proceso %d", getpid());
        mostrarListaMalloc(*listas);
        mostrarListaShared(*listas);
        mostrarListaMmap(*listas);
    }

    return 0;
}

int io(char *tokens[], int ntokens, structListas *listas) {
    if(strcmp(tokens[0], "-read") == 0) {
        do_I_O_read(tokens);
    } else if(strcmp(tokens[0], "-write") == 0) {
        do_I_O_write(tokens);
    }

    return 0;
}

int memdump(char *tokens[], int ntokens, structListas *listas) {

    return 0;
}

int memfill(char *tokens[], int ntokens, structListas *listas) {
    char *ptr;

    // Pasamos todos los datos de tokens a su tipo de dato correspondiente
    void * addr = (void *) strtoul(tokens[0], &ptr, 16);
    size_t cont = strtoul(tokens[1], &ptr, 10);
    unsigned char byte = strtoul(tokens[2], &ptr, 10);

    LlenarMemoria(addr, cont, byte);
    
    return 0;
}

int memory(char *tokens[], int ntokens, structListas *listas) {
    int local1 = 1, local2 = 2, local3 = 3;
    int static static1 = 1, static2 = 2, static3 = 3;
    if(strcmp(tokens[0], "-blocks") == 0) {
        printf("*** Lista de bloques asignados para el proceso %d", getpid());
        mostrarListaMalloc(*listas);
        mostrarListaShared(*listas);
        mostrarListaMmap(*listas);

    } else if(strcmp(tokens[0], "-funcs") == 0) {
        printf("Funciones programa\t %p,\t %p,\t %p \n", memory, autores, pid);
        printf("Funciones librería\t %p,\t %p,\t %p \n", printf, scanf, strcmp);
    } else if(strcmp(tokens[0], "-vars") == 0) {
        printf("Variables locales\t %p,\t %p,\t %p \n", &local1, &local2, &local3);
        printf("Variables globales\t %p,\t %p,\t %p \n", &global1, &global2, &global3);
        printf("Variables estaticas\t %p,\t %p,\t %p \n", &static1, &static2, &static3);
    } else if(strcmp(tokens[0], "-all") == 0) {
        printf("Variables locales\t %p,\t %p,\t %p \n", &local1, &local2, &local3);
        printf("Variables globales\t %p,\t %p,\t %p \n", &global1, &global2, &global3);
        printf("Variables estaticas\t %p,\t %p,\t %p \n", &static1, &static2, &static3);
        printf("Funciones programa\t %p,\t %p,\t %p \n", memory, autores, pid);
        printf("Funciones librería\t %p,\t %p,\t %p \n", printf, scanf, strcmp);
        printf("*** Lista de bloques asignados para el proceso %d", getpid());
        mostrarListaMalloc(*listas);
        mostrarListaShared(*listas);
        mostrarListaMmap(*listas);

    } else if(strcmp(tokens[0], "-pmap") == 0) {
        Do_pmap();
    } else {
        printf("Parámetro no válido");
    }



    return 0;
}

int recurse(char *tokens[], int ntokens, structListas *listas) {
    if(ntokens == 1) {
        Recursiva(atoi(tokens[0]));
    }
    return 0;
}

