/*
    Login: a.becerra
    Login: adrian.rego
    Nombre: Alejandro Becerra Suarez
    Nombre: Adrián Rego Criado
*/

#include "funcionesAuxiliares.h"

int splitString(char *cadena, char *trozos[]) {
    int i=1;

    if((trozos[0] = strtok(cadena, " \n\t")) == NULL) {
        return 0;
    }

    while((trozos[i] = strtok(NULL, " \n\t")) != NULL) {
        i++;
    }

    return i;
}

struct cmd {
    char *cmdName; // Nombre con el que llamamos a una función
    int (*cmdFunction)(char *tokens[], int ntokens, structListas *listas); // Nombre de la función y sus parámetros
    char *ayudaCmd[MAX_LENGTH]; // Almacena el mensaje de ayuda de cada comando
};

struct cmd cmds[] = {
        {"autores", autores, "[-n] Imprime los nombres de los autores.\n[-l] Imprime los login de los autores.\n[] Imprime las dos cosas."},
        {"pid", pid, "[] Imprime el pid del proceso que esta ejecutando el shell.\n[-p] Imprime el pid del proceso padre del shell."},
        {"carpeta", carpeta, "[direct] Cambia el directorio de trabajo actual del shell para direct.\n[] Imprime el directorio de trabajo actual."},
        {"fecha", fecha, "[-d] Imprime la fecha actual en formato: at DD/MM/YYYY.\n[-h] Imprime la fecha actual en formato: h:mm:ss.\n[] Imprime la fecha actual en los dos formatos."},
        {"hist", hist, "[] Imprime la lista de comandos usados anteriormente con un número asignado a cada uno.\n[-c] Vacía la lista de comandos guardados.\n[-N] Imprime los primeros N comandos."},
        {"comando", comando, "[-N] Ejecuta el comando en la posición N del historial"},
        {"infosis", infosis, "Imprime información en la máquina que ejecuta el shell."},
        {"ayuda", ayuda, "[] Imprime una lista de los comandos disponibles.\n[cmd] Imprime un poco de ayuda del comando cmd."},
        {"fin", fin, "Acaba la ejecución del shell."},
        {"salir", salir, "Acaba la ejecución del shell."},
        {"bye", bye, "Acaba la ejecución del shell."},
        {"create", create, "[] Crea una carpeta. \n [-f] Crea un fichero."},
        {"stat", stats, "[] Lista los ficheros. \n [-long] Usa el formato largo. \n [-acc] Modifica la hora del último acceso. \n [link] Si hay enlace simbólico, muestra a que hace referencia"},
        {"list", list, "[] Lista el contenido de directorios. \n [-reca] Lo hace recursivamente antes. \n [-recb] Recursivamente después. \n [-hid] Muestra también los fichero ocultos. \n [-long] Usa el formato largo. \n [-acc] Modifica la hora del último acceso. \n [link] Si hay enlace simbólico, muestra a que hace referencia."},
        {"delete", delete, "[name1, name2...] Elimina los ficheros o directorios vacíos que se pasan como parámetro."},
        {"deltree", deltree, "[name1, name2...] Elimina los ficheros o directorios vacíos de forma recursiva."},
        {"allocate", allocate, "[] Asigna un bloque de memoria. \n [-malloc tam] Asigna un bloque malloc de tamaño tam. \n [-shared cl] Asigna el bloque de memoria compartida (ya existe) de clave cl. \n [-createshared cl tam] Asigna (creando) el bloque de memoria compartida de clave cl y tamaño tam. \n [-mmap fich perm] mapea el fichero fich, perm son los permisos."},
        {"deallocate", deallocate, "[] Desasigna un bloque de memoria. \n [-malloc tam] Desasigna un bloque malloc de tamano tam. \n [-shared cl] Desasigna (desmapea) el bloque de memoria compartida de clave cl. \n [-delkey cl] Elimina del sistema (sin desmapear) la clave de memoria cl. \n [-mmap fich] Desmapea el fichero mapeado fich. \n [-addr] Desasigna el bloque de memoria en la dirección addr."},
        {"i-o", io, "[read <fich> <addr> <cont>] Lee cont bytes desde fich a addr. \n [write [-o] <fich> <addr> <cont>] Escribe cont bytes desde addr a fich. -o para sobreescribir addr es una dirección de memoria."},
        {"memdump", memdump, "[<addr> <cont>] Vuelca en pantallas los contenidos (cont bytes) de la posición de memoria adrr."},
        {"memfill", memfill, "[<addr> <cont> <byte>] Llena la memoria a partir de addr con byte."},
        {"memory", memory, "[] Muestra detalles de la memoria del proceso. \n [-blocks] Los bloques de memoria asignados. \n [-funcs] Las direcciones de las funciones. \n [-vars] Las direcciones de las variables. \n [-all] todo. \n [-pmap] Muestra la salida del comando pmap(o similar)."},
        {"recurse", recurse, "[N] Invoca a la función recursiva N veces."},
        {"priority", priority, "[pid] [valor]\tMuestra o cambia la prioridad del proceso <pid> a <valor>"},
        {"showvar", showvar, "<var>\tMuestra el valor y las direcciones de la variable de entorno var"},
        {"changevar", changevar, "[-a|-e|-p] var valor\tCambia el valor de una variable de entorno\n\t-a: accede por el tercer arg de main\n\t-e: accede mediante environ\n\t-p: accede mediante putenv"},
        {"showenv", showenv, "[-environ|-addr] \t Muestra el entorno del proceso\n\t-environ: accede usando environ (en lugar del tercer arg de main)\n\t-addr: muestra el valor y donde se almacenan environ y el 3er arg main"},
        {"fork", forkA, "\tEl shell hace fork y queda en espera a que su hijo termine"},
        {"execute", execute, "VAR1 VAR2 ..prog args....[@pri]\tEjecuta, sin crear proceso,prog con argumentos\n\t en un entorno que contiene solo las variables VAR1, VAR2..."},
        {"listjobs", listjobs, "\tLista los procesos en segundo plano"},
        {"deljobs", deljobs, "[-term][-sig]\tElimina los procesos de la lista procesos en sp\n\t-term: los terminados\n\t-sig: los terminados por senal"},
        {"job", job, "[-fg] pid\tMuestra informacion del proceso pid.\n\t\t-fg: lo pasa a primer plano"},
        {NULL, NULL}
};

int processInput(char *tokens[], int ntokens, structListas *listas) {
    int exit = 0;

    for(int i = 0; cmds[i].cmdName != NULL; i++) { // Se busca el nombre del comando en el struct de arriba
        if(strcmp(tokens[0], cmds[i].cmdName) == 0) {
            exit = cmds[i].cmdFunction(tokens + 1, ntokens - 1, listas); // Cuando se encuentra se ejecuta la función asociada
            return exit;
        }
    }

    pid_t pid = fork();

    if(pid == 0) {
        if(strcmp(tokens[ntokens - 1], "&") == 0) {
            tokens[ntokens - 1] = NULL;
            ntokens--;
            execute(tokens, ntokens, listas);

        } else {
            execute(tokens, ntokens, listas);
        }

        return 1;

    } else if(pid > 0) {
        if(strcmp(tokens[ntokens - 1], "&") != 0) {
            waitpid(pid, NULL, 0);

        } else if(strcmp(tokens[ntokens - 1], "&") == 0) {
            char fecha[MAX_LENGTH];
            struct job *j = malloc(sizeof(struct job));
            j->pid = pid;

            int senal;
           /* pid_t result = waitpid(pid, &senal, WNOHANG);
            //wait(&senal);
            strcpy(j->state, NombreSenal(senal));*/

            time_t tm = time(NULL);
            strftime(fecha, MAX_LENGTH, "%b %d %H:%M ", localtime(&tm));

            strcpy(j->fecha, fecha);
            strcpy(j->uName, getlogin());
            strcpy(j->name, tokens[0]);

            insert(&listas->job, j);

            return 0;

        } else {
            perror("Error al crear el proceso hijo");
            return 1;
        }
    }

    /*if(strcmp(tokens[ntokens - 1], "&") != 0) {
        pid_t pid = fork();

        if(pid == 0) {
            // Este es el código que se ejecutará en el proceso hijo
            execute(tokens, ntokens, listas);
            return 1;
        } else if(pid > 0) {
            // Este es el código que se ejecutará en el proceso padre
            // Espera a que el proceso hijo termine
            waitpid(pid, NULL, 0);

        } else {
            perror("Error al crear el proceso hijo");
            return 1;
        }
    } else if(strcmp(tokens[ntokens - 1], "&") == 0){
        pid_t pid = fork();

        //printf("tokens[0]: %s\nntokens: %d", tokens[0], ntokens);
        if(pid > 0) {*/
            /*char fecha[MAX_LENGTH];
            struct job *j = malloc(sizeof(struct job));
            j->pid = pid;
            strcpy(j->state, NombreSenal(kill(pid, 0)));

            time_t tm = time(NULL);
            strftime(fecha, MAX_LENGTH, "%b %d %H:%M ", localtime(&tm));

            strcpy(j->fecha, fecha);
            strcpy(j->uName, getlogin());
            strcpy(j->name, tokens[0]);

            insert(&listas->job, j);*/
            /*return exit;
        } else if(pid == 0) {
            ntokens--;
            char *aux[ntokens];

            for(int i = 0; i < ntokens; i++) {
                aux[i] = tokens[i];
                //strcpy(aux[i], tokens[i]);
            }
            // Este es el código que se ejecutará en el proceso hijo
            execute(aux, ntokens, listas);
            return 1;
        }



        if(pid < 0) {
            perror("Error al crear el proceso hijo");
            return 1;
        }
    }*/



    return exit;
}

// Se hace el mismo proceso que con processInput, pero se muestra por pantalla lo almacenado en ayudaCmd
int ayuda(char *tokens[], int ntokens, structListas *listas) {
    if(tokens[0] != NULL) {
        for(int i=0; cmds[i].cmdName != NULL; i++) {
            if(strcmp(tokens[0], cmds[i].cmdName) == 0) {
                printf("%s %s\n", cmds[i].cmdName, *cmds[i].ayudaCmd);
            }
        }
    } else {
        printf("ayuda [cmd] siendo cmd uno de los siguientes comandos:\n");
        for(int i=0; cmds[i].cmdName != NULL; i++) { // Muestra los comando disponibles
            printf(" %s |",cmds[i].cmdName);
        }
        printf("\n");
    }

    return 0;
}

char LetraTF (mode_t m)
{
    switch (m&S_IFMT) { /*and bit a bit con los bits de formato,0170000 */
        case S_IFSOCK: return 's'; /*socket */
        case S_IFLNK: return 'l'; /*symbolic link*/
        case S_IFREG: return '-'; /* fichero normal*/
        case S_IFBLK: return 'b'; /*block device*/
        case S_IFDIR: return 'd'; /*directorio */
        case S_IFCHR: return 'c'; /*char device*/
        case S_IFIFO: return 'p'; /*pipe*/
        default: return '?'; /*desconocido, no deberia aparecer*/
    }
}

// Las dos siguientes son dadas como código de ayuda en la página web de la asignatura
/*las siguientes funciones devuelven los permisos de un fichero en formato rwx----*/
/*a partir del campo st_mode de la estructura stat */
/*las tres son correctas pero usan distintas estrategias de asignación de memoria*/

char * ConvierteModo2 (mode_t m)
{
    static char permisos[12];
    strcpy (permisos,"---------- ");

    permisos[0]=LetraTF(m);
    if (m&S_IRUSR) permisos[1]='r';    /*propietario*/
    if (m&S_IWUSR) permisos[2]='w';
    if (m&S_IXUSR) permisos[3]='x';
    if (m&S_IRGRP) permisos[4]='r';    /*grupo*/
    if (m&S_IWGRP) permisos[5]='w';
    if (m&S_IXGRP) permisos[6]='x';
    if (m&S_IROTH) permisos[7]='r';    /*resto*/
    if (m&S_IWOTH) permisos[8]='w';
    if (m&S_IXOTH) permisos[9]='x';
    if (m&S_ISUID) permisos[3]='s';    /*setuid, setgid y stickybit*/
    if (m&S_ISGID) permisos[6]='s';
    if (m&S_ISVTX) permisos[9]='t';

    return permisos;
}

/**
 * Calcula el tamaño del fichero y lo retorna
 *
 * @param file - Fichero del que queremos calcular el tamaño
 * @return El tamaño del fichero
 */
off_t tamanoFichero(char *file) {     //Returns size of one file
    struct stat size;

    if(stat(file,&size) == -1) {
        return -1;
    }

    return size.st_size;
}

/**
 * Imprime la información de la ruta que le pasemos como parámetro por tokens
 * @param tokens - Ruta para imprimir la información
 * @param flags - Parámetros que mostrarán una información u otra
 * @return 0 si todo fue correcto, -1 si el fichero no existe o si los usuarios furon borrados
 * , o 1 si no se pudieron cargar los datos del archivo
 */
int printStatAndList(char *tokens, SStatListCommand flags) {
    char fecha[MAX_LENGTH];
    struct tm fechaYHora;
    char formatoFechaYHora[] = "%Y/%m/%d-%H:%M";
    struct stat datos; // número de links, número de inodos y tamaño del archivo
    struct passwd *usuario; // El struct passwd, contiene información del usuario
    struct group *grupo; // El struct group, contiene información del grupo
    char *permisos; // Los permisos si no tienen valor tienen un guion
    char linkSimbolico[MAX_LENGTH];
    long espacio = tamanoFichero(tokens);

    if(lstat(tokens, &datos) == -1) { // Carga en datos la información del archivo
        return 1;
    }

    if(!flags.longFlag) {
        if(espacio == -1) {
            return -1;
        }

        printf("%ld\t%s\n", espacio, tokens);

    } else {
        (flags.accFlag)? (localtime_r(&datos.st_atime, &fechaYHora)) : (localtime_r(&datos.st_mtime, &fechaYHora));


        // Guarda los datos de usuario, grupos y permisos
        if(getpwuid(datos.st_uid) != NULL) {
            usuario = getpwuid(datos.st_uid);
        } else {
            return -1;
        }

        if(getgrgid(datos.st_gid) != NULL) {
            grupo = getgrgid(datos.st_gid);
        } else {
            return -1;
        }

        permisos = ConvierteModo2(datos.st_mode);

        strftime(fecha, MAX_LENGTH, formatoFechaYHora, &fechaYHora);
        printf("%s\t%ld \t(%8ld)\t%s    \t%s    \t%s\t%ld\t\t%s",
               fecha,
               datos.st_nlink,
               datos.st_ino,
               usuario->pw_name,
               grupo->gr_name,
               permisos,
               datos.st_size,
               tokens);

        // Si el flag de links simbólicos y la función readlink dan true, mostrará el link
        // Cuando readlink falla retorna un -1
        if(flags.linkFlag && (readlink(tokens, linkSimbolico, MAX_LENGTH) != -1)) {
            strcat(linkSimbolico, "\0");
            printf(" --> %s\n", linkSimbolico);

        } else {
            printf("\n");
        }
    }
    return 0;
}

int isDirectory(char *tokens) { // Comprueba si tokens es un directorio
    struct stat st;
    stat(tokens, &st);

    int isDirectory = S_ISDIR(st.st_mode);
    return isDirectory;
}

/**
 *
 * @param path - Ruta a eliminar
 * @return 0 si todo fue correcto, -1 si no se puede abrir el directorio
 */
int delete_item(char *path) {
    char nuevaRuta[MAX_LENGTH];
    DIR *directorio;
    struct dirent *entrada;
    struct stat st;

    if((directorio = opendir(path)) == NULL) {
        return -1;
    }

    while((entrada = readdir(directorio)) != NULL) {
        strcpy(nuevaRuta, path);
        strcat(strcat(nuevaRuta, "/"),entrada->d_name);

        if(strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0) {
            continue;
        }

        lstat(nuevaRuta, &st);

        if((st.st_mode & S_IFMT) == S_IFDIR) {
            delete_item(nuevaRuta);
        }

        if(remove(nuevaRuta)) {
            return -1;
        }
    }
    closedir(directorio);

    return 0;
}

/**
 * Lista el contenido de la ruta introducida
 * @param tokens - Nombre de la ruta introducida
 * @param flags - Parámetros para mostrar la información
 * @param ntokens - Cantidad de rutas que hay en el comando
 * @return 0 si todo es correcto, -1 si no se puede abrir la ruta
 */
int listarCarpeta(char *tokens, SStatListCommand flags, int ntokens) {
    struct stat st;
    char previousDirectory[MAX_LENGTH], directory[MAX_LENGTH];
    DIR *direct; // Tipo de variable para directorios
    struct dirent *entrada;

    getcwd(previousDirectory,sizeof(previousDirectory)); // Guardamos el directorio actual por si nos tenemos que mover
    chdir(tokens);                           // Nos cambiamos de directorio
    getcwd(directory, sizeof(directory));   // Guardamos la nueva ruta

    lstat(tokens, &st); // Cargamos en st, al archivo de tokens

    if((direct = opendir(directory)) == NULL) {
        printf("Could not open %s: %s\n", tokens, strerror(errno));
        return -1;
    } else {
        printf("\n*** %s\n", tokens);

        entrada = readdir(direct); // Guarda los datos del directorio direct en entrada

        do {
            // Si se escribe el parámetro -hid, y el nombre del archivo empieza por punto, se lo salta
            if (!flags.hidFlag && (entrada->d_name[0] == '.')) {
                continue;
            } else {
                printStatAndList(entrada->d_name, flags);
            }

        } while ((entrada = readdir(direct)) != NULL);

        closedir(direct); // Cierra el directorio una vez se enseñó su contenido
    }

    chdir(previousDirectory);  // Después de listar los archivos volvemos al directorio inicial

    return 0;
}

/**
 * Lista todos los archivos de forma recursiva que hay en el arbol de directrios
 * a partir del path introducido.
 * @param path - Ruta de una carpeta
 * @param flags - Struct con los parámetros que se usarán para mostrar información
 * @return 0 si todo es correcto
 */
int listaArbolCarpetas(char *path, SStatListCommand flags) {
    char nuevaRuta[MAX_LENGTH];
    DIR *directorio;
    struct dirent *entrada;
    char nuevaEntrada[MAX_LENGTH];
    struct stat st;

    if((directorio = opendir(path)) != NULL) {
        while((entrada = readdir(directorio)) != NULL) {
            // Hace que no entre ni en . ni .., para evitar una recursión infinita
            if(strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0) {
                continue;
            }

            // Si listamos /, conatenamos de otra forma para evitar el // del concatenado habitual
            if(strcmp(path, "/") == 0) {
                strcat(strcpy(nuevaRuta, "/"),entrada->d_name);
            } else {
                strcpy(nuevaRuta, path);
                strcat(strcat(nuevaRuta, "/"),entrada->d_name);
            }

            lstat(nuevaRuta, &st);

            if((st.st_mode & S_IFMT) == S_IFDIR) {
                strcpy(nuevaEntrada, entrada->d_name);

                if(nuevaEntrada[0] == '.' && !flags.hidFlag) {
                    continue;

                } else {
                    // Si es una carpeta se lista su contenida
                    if(flags.recbFlag && !flags.recaFlag) listaArbolCarpetas(nuevaRuta, flags);
                    listarCarpeta(nuevaRuta, flags, 1);
                    if(flags.recaFlag) listaArbolCarpetas(nuevaRuta, flags);
                }

            }

        }
    }

    closedir(directorio);
    return 0;
}

/**
 * Esta función lista todos los elementos que hay guardados
 * en la lista de malloc, y con un formato específico
 *
 * @param L Lista introducida para lista el malloc
 */
void mostrarListaMalloc(structListas L) {
    for(pos p = first(L.allocateMalloc); !at_end(L.allocateMalloc, p); p = next(L.allocateMalloc, p)) {
        struct allocateMalloc *LMB = get(L.allocateMalloc, p);
        //char fecha[MAX_LENGTH];
        //strftime(fecha, MAX_LENGTH,"%b %d %H:%M ", LMB->tm);

        printf("\n%p\t\t%ld %s malloc", LMB->memoryAddress, LMB->size, LMB->fecha);
    }
}

/**
 * Esta función lista todos los elementos que hay guardados
 * en la lista de shared, y con un formato específico
 *
 * @param L Lista introducida para lista el shared
 */
void mostrarListaShared(structListas L) {
    for(pos p = first(L.allocateShared); !at_end(L.allocateShared, p); p = next(L.allocateShared, p)) {
        struct allocateShared *LMB = get(L.allocateShared, p);
        //char fecha[MAX_LENGTH];
        //strftime(fecha, MAX_LENGTH,"%b %d %H:%M ", LMB->tm);

        printf("\n%p\t\t%ld %s shared (key %d)", LMB->memoryAddress, LMB->size, LMB->fecha, LMB->key);
    }
}

/**
 * Esta función lista todos los elementos que hay guardados
 * en la lista de mmap, y con un formato específico
 *
 * @param L Lista introducida para lista el mmap
 */
void mostrarListaMmap(structListas L) {
    for(pos p = first(L.allocateMmap); !at_end(L.allocateMmap, p); p = next(L.allocateMmap, p)) {
        struct allocateMmap *LMB = get(L.allocateMmap, p);
        //char fecha[MAX_LENGTH];
        //strftime(fecha, MAX_LENGTH,"%b %d %H:%M ", LMB->tm);

        printf("\n%p\t\t%ld %s %s (descriptor %d)", LMB->memoryAddress, LMB->size, LMB->fecha, LMB->fich, LMB->descritor);
    }
}

void do_AllocateMalloc(char *tokens[], structListas *L) {
    time_t t = time(NULL);
    char fecha[MAX_LENGTH];
    void *memoryAddress;

    struct allocateMalloc *LMB = malloc(sizeof(struct allocateMalloc));
    int size = atoi(tokens[1]);
    memoryAddress = malloc(*tokens[1]);
    LMB->memoryAddress = memoryAddress;
    LMB->size = size;

    strftime(fecha, MAX_LENGTH,"%b %d %H:%M ", localtime(&t));
    strcpy(LMB->fecha,fecha);

    printf("Asignados %d bytes en %p", size, LMB->memoryAddress);

    insert(&L->allocateMalloc, LMB);
}

/**
 * Crea una zona de memoria compartida a partir de una clave
 *
 * @param clave - Clave de la memoria compartida
 * @param tam - Tamaño de la memoria, si es 0 no se crea una clave nueva
 * @param L - Lista en la que se insertarán los datos
 * @return
 */
void * ObtenerMemoriaShmget (key_t clave, size_t tam, structListas *L) {
    void * p;
    int aux,id,flags=0777;
    struct shmid_ds s;
    char fecha[MAX_LENGTH];
    time_t t = time(NULL);

    if(tam) {    /*tam distinto de 0 indica crear */
        flags = flags | IPC_CREAT | IPC_EXCL;
    }

    if(clave == IPC_PRIVATE) { /*no nos vale*/
        errno = EINVAL;
        return NULL;
    }

    if((id = shmget(clave, tam, flags)) == -1) {
        return (NULL);
    }

    if((p = shmat(id,NULL,0)) == (void*) -1) {
        aux = errno;

        if(tam) {
            shmctl(id,IPC_RMID,NULL);
        }
        errno = aux;
        return (NULL);
    }

    shmctl(id,IPC_STAT,&s);
    /* Guardar en la lista   InsertarNodoShared (&L, p, s.shm_segsz, clave); */
    struct allocateShared *LMB = malloc(sizeof(struct allocateShared));
    LMB->memoryAddress = p;
    LMB->size = s.shm_segsz;
    strftime(fecha, MAX_LENGTH,"%b %d %H:%M ", localtime(&t));
    strcpy(LMB->fecha,fecha);
    LMB->key = clave;

    insert(&L->allocateShared, LMB);

    return (p);
}

/**
 *  Crea una zona de memoria compartida a partir de una clave introducida
 *  por el usuario
 *
 * @param tr - Parámetros para crear la clave, key tamaño
 * @param L - Lista en la que se insertará la información del bloque
 */
void do_AllocateCreateshared (char *tr[], structListas L)
{
    key_t cl;
    size_t tam;
    void *p;

    if (tr[1]==NULL || tr[2]==NULL) {
        printf("*** Lista de bloques asignados con shared para el proceso %d", getpid());
        mostrarListaShared(L);
        return;
    }

    cl=(key_t)  strtoul(tr[1],NULL,10);
    tam=(size_t) strtoul(tr[2],NULL,10);
    if (tam==0) {
        printf ("No se asignan bloques de 0 bytes");
        return;
    }
    if ((p=ObtenerMemoriaShmget(cl,tam, &L))!=NULL) {
        printf ("Asignados %lu bytes en %p",(unsigned long) tam, p);
    } else {
        printf("Imposible asignar memoria compartida clave %lu:%s\n",
               (unsigned long) cl, strerror(errno));
    }
}

/**
 * Mapea un archivo con los permisos indicados
 *
 * @param fichero - Nombre del fichero a mapear
 * @param protection - Permisos del fichero
 * @param L - Lista en la que se insertarán los datos correspondientes
 * @return - Dirección en la que se mapea el archivo
 */
void * MapearFichero(char * fichero, int protection, structListas *L) {
    int df, map=MAP_PRIVATE,modo=O_RDONLY;
    struct stat s;
    void *p;
    time_t t = time(NULL);
    char fecha[MAX_LENGTH];

    if(protection&PROT_WRITE) {
        modo = O_RDWR;
    }

    if(stat(fichero,&s) == -1 || (df=open(fichero, modo))==-1) {
        return NULL;
    }

    if((p=mmap (NULL,s.st_size, protection,map,df,0))==MAP_FAILED) {
        return NULL;
    }

    /* Guardar en la lista    InsertarNodoMmap (&L,p, s.st_size,df,fichero); */
    struct allocateMmap *LMB = malloc(sizeof(struct allocateMmap));

    LMB->memoryAddress = p;
    LMB->size = s.st_size;
    strftime(fecha, MAX_LENGTH,"%b %d %H:%M ", localtime(&t));
    strcpy(LMB->fecha,fecha);
    LMB->descritor = df;
    strcpy(LMB->fich, fichero);

    insert(&L->allocateMmap, LMB);

    return p;
}

/**
 * Función principal del mapeo de un fichero
 *
 * @param arg - Parámetros para el mapeo
 * @param L - Lista en la que se insertarán los datos del mapeo
 */
void do_AllocateMmap(char *arg[], structListas L) {
    char *perm;
    void *p;
    int protection=0;

    if(arg[1]==NULL) {
        printf("*** Lista de bloques asignados con mmap para el proceso %d", getpid());
        mostrarListaMmap(L);
        return;
    }
    if((perm=arg[2])!=NULL && strlen(perm)<4) {
        if (strchr(perm,'r')!=NULL) protection|=PROT_READ;
        if (strchr(perm,'w')!=NULL) protection|=PROT_WRITE;
        if (strchr(perm,'x')!=NULL) protection|=PROT_EXEC;
    }
    if((p=MapearFichero(arg[1],protection, &L))==NULL) {
        perror("Imposible mapear fichero");
    } else {
        printf("fichero %s mapeado en %p", arg[1], p);
    }
}

/**
 * Libera el primer malloc que tenga el tamaño indicado en la entrada
 *
 * @param L - Lista en la que buscará la memoria d liberar
 * @param tam - Tamaño que se liberará
 */
void deallocateMalloc(structListas L, long int tam) {
    for(pos p = first(L.allocateMalloc); !at_end(L.allocateMalloc, p); p = next(L.allocateMalloc, p)) {
        struct allocateMalloc *LMB = get(L.allocateMalloc, p);

        if(LMB->size == tam) {
            free(LMB->memoryAddress);
            deleteAtPosition(&L.allocateMalloc, p);
            break;
        }
    }
}

/**
 * Desmapea la primera zona de memoria compartida que tenga la memoria indicada
 *
 * @param L - Lista en la que buscará la memoria d liberar
 * @param key - Clave que se buscará
 */
void deallocateShared(structListas L, key_t key) {
    for(pos p = first(L.allocateShared); !at_end(L.allocateShared, p); p = next(L.allocateShared, p)) {
        struct allocateShared *LMB = get(L.allocateShared, p);

        if(LMB->key == key) {
            shmdt(LMB->memoryAddress);
            deleteAtPosition(&L.allocateShared, p);
            break;
        }
    }
}

/**
 * Crea una clave y una zona de memoria compartida con el tamaño indicado
 *
 * @param args - Parámetros de entrada, clave tamaño
 */
void do_DeallocateDelkey (char *args[]) {
    key_t clave;
    int id;
    char *key=args[1];

    if (key==NULL || (clave=(key_t) strtoul(key,NULL,10))==IPC_PRIVATE){
        printf ("      delkey necesita clave_valida\n");
        return;
    }

    if ((id=shmget(clave,0,0666))==-1){
        perror ("shmget: imposible obtener memoria compartida");
        return;
    }

    if (shmctl(id,IPC_RMID,NULL)==-1)
        perror ("shmctl: imposible eliminar memoria compartida\n");

}

/**
 * Despmapea al archivo escrito en la entrada
 *
 * @param L - Lista sobre la que se buscará la dirección
 * @param args - Fichero para despmapear
 */
void deallocateMmap(structListas L, char *args[]) {
    for(pos p = first(L.allocateMmap); !at_end(L.allocateMmap, p); p = next(L.allocateMmap, p)) {
        struct allocateMmap *LMB = get(L.allocateMmap, p);

        if(strcmp(LMB->fich, args[1]) == 0) {
            munmap(LMB->memoryAddress, LMB->size);
            deleteAtPosition(&L.allocateMmap, p);
            break;
        }
    }
}

/**
 * Reibiendo una dirección n, libera el espacio en memoria y elimina el su
 * registro de la lista correspondiente. Si no está en la lista muestra un
 * mensaje explicativo.
 *
 * @param L - Listas en las que se mirará si está o no
 * @param n - Dirección a eliminar
 */
void deallocateAddr(structListas L, void *n) {
    for(pos p = first(L.allocateMalloc); !at_end(L.allocateMalloc, p); p = next(L.allocateMalloc, p)) {
        struct allocateMalloc *LMB = get(L.allocateMalloc, p);

        if(LMB->memoryAddress == n) {
            free(LMB->memoryAddress);
            deleteAtPosition(&L.allocateMalloc, p);
            return;
        }
    }

    for(pos p = first(L.allocateShared); !at_end(L.allocateShared, p); p = next(L.allocateShared, p)) {
        struct allocateShared *LMB = get(L.allocateShared, p);

        if(LMB->memoryAddress == n) {
            shmdt(LMB->memoryAddress);
            deleteAtPosition(&L.allocateShared, p);
            return;
        }
    }

    for(pos p = first(L.allocateMmap); !at_end(L.allocateMmap, p); p = next(L.allocateMmap, p)) {
        struct allocateMmap *LMB = get(L.allocateMmap, p);

        if(LMB->memoryAddress == n) {
            munmap(LMB->memoryAddress, LMB->size);
            deleteAtPosition(&L.allocateMmap, p);
            return;
        }
    }

    printf("La dirección dada no se encontró para poder ejecutar deallocate.");

}

ssize_t LeerFichero(char *f, void *p, size_t cont) {
    struct stat s;
    ssize_t  n;
    int df,aux;

    if(stat(f,&s) == -1 || (df = open(f,O_RDONLY)) == -1) {
        return -1;
    }

    if(cont == -1) { /* si pasamos -1 como bytes a leer lo leemos entero*/
        cont = s.st_size;
    }

    if((n = read(df,p,cont)) == -1) {
        aux=errno;
        close(df);
        errno=aux;
        return -1;
    }

    close (df);
    return n;
}

void do_I_O_read (char *ar[]) {
    void *p;
    size_t cont = -1;
    ssize_t n;

    if(ar[1] == NULL || ar[2] == NULL) {
        printf ("faltan parametros\n");
        return;
    }

    p = (void *) strtoul(ar[2], NULL, 16); /*convertimos de cadena a puntero*/
    
    if(ar[3] != NULL) {
        cont = (size_t) atoll(ar[3]);
    }

    if((n = LeerFichero(ar[1], p, cont)) == -1) {
        perror("Imposible leer fichero");

    } else {
        printf("leidos %lld bytes de %s en %p\n", (long long) n, ar[1], p);
    }
}

ssize_t EscribirFichero(char *f, void *p, size_t cont,int overwrite) {
    ssize_t  n;
    int df,aux, flags=O_CREAT | O_EXCL | O_WRONLY;

    if(overwrite) {
        flags = O_CREAT | O_WRONLY | O_TRUNC;
    }

    if((df=open(f,flags,0777)) == -1) {
        return -1;
    }

    if((n=write(df,p,cont)) == -1) {
        aux=errno;
        close(df);
        errno=aux;
        return -1;
    }

    close (df);
    return n;
}

void do_I_O_write(char *ar[]) {
    void *p;
    size_t cont=-1;
    ssize_t n;
    int overwrite = 0;

    if(strcmp(ar[1], "-o") == 0) {
        overwrite = 1;
    }

    if(ar[1 + overwrite]==NULL || ar[2 + overwrite]==NULL) {
        printf ("faltan parametros\n");
        return;
    }

    p = (void *) strtoul(ar[2 + overwrite], NULL, 16);  /*convertimos de cadena a puntero*/
    if(ar[3 + overwrite]!=NULL) {
        cont = (size_t) atoll(ar[3 + overwrite]);
    }

    if((n=EscribirFichero(ar[1 + overwrite], p, cont, overwrite)) == -1) {
        perror("Imposible escribir fichero");
    } else {
        printf("Escritos %lld bytes de %s en %p", (long long) n, ar[1 + overwrite], p);
    }
}

/**
 * Llena una zona de memoria desde p y cont bytes, con el byte escrito por la
 * entrada
 *
 * @param p - Dirección de memoria que comenzará a llenarse
 * @param cont - Cantidad de bytes que se llenarán
 * @param byte - El byte con el que se llenará la dirección indicada
 */
void LlenarMemoria (void *p, size_t cont, unsigned char byte) {
    unsigned char *arr = (unsigned char *) p;
    size_t i;

    for(i=0; i<cont; i++) {
        arr[i] = byte;
    }

    printf("Llenando %lu bytes de memoria con el byte %c(%02X) a partir de la dirección %p", i, byte, byte, arr);

}

void Do_pmap(void) {/*sin argumentos*/
    pid_t pid;       /*hace el pmap (o equivalente) del proceso actual*/
    char elpid[32];
    char *argv[4]={"pmap",elpid,NULL};

    sprintf (elpid,"%d", (int) getpid());
    if((pid=fork())==-1){
        perror ("Imposible crear proceso");
        return;
    }

    if(pid==0){
        if(execvp(argv[0],argv) == -1) {
            perror("cannot execute pmap (linux, solaris)");
        }

        argv[0] = "procstat"; argv[1] = "vm"; argv[2] = elpid; argv[3] = NULL;
        if(execvp(argv[0],argv)==-1) {/*No hay pmap, probamos procstat FreeBSD */
            perror("cannot execute procstat (FreeBSD)");
        }

        argv[0] = "procmap", argv[1] = elpid; argv[2] = NULL;
        if(execvp(argv[0], argv) == -1) { /*probamos procmap OpenBSD*/
            perror("cannot execute procmap (OpenBSD)");
        }

        argv[0] = "vmmap"; argv[1] = "-interleave"; argv[2] = elpid; argv[3] = NULL;
        if(execvp(argv[0], argv) == -1) {/*probamos vmmap Mac-OS*/
            perror("cannot execute vmmap (Mac-OS)");
        }

        exit(1);
    }
    waitpid(pid,NULL,0);
}

/**
 * Muestra un printf que enseña direcciones de memoria de forma recursiva
 * @param n - Número de veces que queremos que se repita la función recursiva
 */
void Recursiva(int n) {
    char automatico[MAX_LENGTH];
    static char estatico[MAX_LENGTH];

    printf("parametro:%3d(%p) array %p, arr estatico %p", n, &n, automatico, estatico);

    if(n>0) {
        Recursiva(n-1);
    }

}

/**
 * Libera memoria de la lista
 * @param - addr Dirección que usará el deleteList para liberar la lista
 */
void liberarMalloc(void *addr) {
    struct allocateMalloc *liberar = addr;

    // Liberamos la dirección de memoria de los malloc con free
    free(liberar->memoryAddress);
    free(liberar);
}

/**
 * Libera memoria de la lista
 * @param - addr Dirección que usará el deleteList para liberar la lista
 */
void liberarShared(void *addr) {
    struct allocateShared *liberar = addr;

    // Liberamos la dirección de memoria de la zona compartida con shmdt
    shmdt(liberar->memoryAddress);
    free(liberar);
}

/**
 * Libera memoria de la lista
 * @param - addr Dirección que usará el deleteList para liberar la lista
 */
void liberarMmap(void *addr) {
    struct allocateMmap *liberar = addr;

    // Liberamos la dirección de memoria de los ficheros mapeados con mmap
    munmap(liberar->memoryAddress, liberar->size);
    free(liberar);
}

int BuscarVariable (char * var, char *e[]) { /*busca una variable en el entorno que se le pasa como parámetro*/
    int posicion=0;
    char aux[MAXVAR];

    strcpy (aux,var);
    strcat (aux,"=");

    while (e[posicion] != NULL)
        if (!strncmp(e[posicion], aux, strlen(aux)))
            return (posicion);
        else
            posicion++;
    errno = ENOENT;   /*no hay tal variable*/
    return(-1);
}

int CambiarVariable(char * var, char * valor, char *e[]) {
  int posicion;
  char *aux;

  if((posicion = BuscarVariable(var, e)) == -1) {
      return (-1);
  }
  if((aux = (char *) malloc(strlen(var) + strlen(valor) + 2)) == NULL) {
      return -1;
  }
  strcpy(aux, var);
  strcat(aux, "=");
  strcat(aux, valor);
  e[posicion] = aux;

  return (posicion);
}

char * Ejecutable (char *s) {
    char path[MAX_LENGTH];
    static char aux2[MAX_LENGTH];
    struct stat st;
    char *p;

    if(s == NULL || (p = getenv("PATH")) == NULL) {
        return s;
    }

    if(s[0] == '/' || !strncmp(s, "./", 2) || !strncmp (s, "../", 3)) {
        return s;
    }       /*is an absolute pathname*/

    strncpy(path, p, MAX_LENGTH);

    for(p = strtok(path, ":"); p != NULL; p = strtok(NULL, ":")) {
       sprintf(aux2, "%s/%s", p, s);

       if(lstat(aux2, &st) != -1) {
           return aux2;
       }
    }
    return s;
}

int OurExecvpe(char *file, char *argv[], char *envp[]) {
   return (execve(Ejecutable(file),argv, envp));
}

int comandoBackground(char *tokens[], int ntokens, structListas *listas) {
    int prioridad = 0;
    char *firstPart = strtok(tokens[ntokens - 1], "@");

    if(strcmp(firstPart, "@") == 0) {
        char *secongPart = strtok(NULL, "@");
        prioridad = atoi(secongPart);
        nice(prioridad);
    }


    return 0;
}

/*las siguientes funciones nos permiten obtener el nombre de una senal a partir
del número y viceversa */
static struct SEN sigstrnum[]={
        {"HUP", SIGHUP},
        {"INT", SIGINT},
        {"QUIT", SIGQUIT},
        {"ILL", SIGILL},
        {"TRAP", SIGTRAP},
        {"ABRT", SIGABRT},
        {"IOT", SIGIOT},
        {"BUS", SIGBUS},
        {"FPE", SIGFPE},
        {"KILL", SIGKILL},
        {"USR1", SIGUSR1},
        {"SEGV", SIGSEGV},
        {"USR2", SIGUSR2},
        {"PIPE", SIGPIPE},
        {"ALRM", SIGALRM},
        {"TERM", SIGTERM},
        {"CHLD", SIGCHLD},
        {"CONT", SIGCONT},
        {"STOP", SIGSTOP},
        {"TSTP", SIGTSTP},
        {"TTIN", SIGTTIN},
        {"TTOU", SIGTTOU},
        {"URG", SIGURG},
        {"XCPU", SIGXCPU},
        {"XFSZ", SIGXFSZ},
        {"VTALRM", SIGVTALRM},
        {"PROF", SIGPROF},
        {"WINCH", SIGWINCH},
        {"IO", SIGIO},
        {"SYS", SIGSYS},

/*senales que no hay en todas partes*/
#ifdef SIGPOLL
        {"POLL", SIGPOLL},
#endif
#ifdef SIGPWR
        {"PWR", SIGPWR},
#endif
#ifdef SIGEMT
        {"EMT", SIGEMT},
#endif
#ifdef SIGINFO
        {"INFO", SIGINFO},
#endif
#ifdef SIGSTKFLT
        {"STKFLT", SIGSTKFLT},
#endif
#ifdef SIGCLD
        {"CLD", SIGCLD},
#endif
#ifdef SIGLOST
        {"LOST", SIGLOST},
#endif
#ifdef SIGCANCEL
        {"CANCEL", SIGCANCEL},
#endif
#ifdef SIGTHAW
        {"THAW", SIGTHAW},
#endif
#ifdef SIGFREEZE
        {"FREEZE", SIGFREEZE},
#endif
#ifdef SIGLWP
        {"LWP", SIGLWP},
#endif
#ifdef SIGWAITING
        {"WAITING", SIGWAITING},
#endif
        {NULL,-1},
};    /*fin array sigstrnum */


int ValorSenal(char * sen) { /*devuelve el numero de senial a partir del nombre*/

    int i;
    for (i=0; sigstrnum[i].nombre!=NULL; i++) {
        if (!strcmp(sen, sigstrnum[i].nombre)) {
            return sigstrnum[i].senal;
        }
    }
    return -1;
}


char *NombreSenal(int sen) { /*devuelve el nombre senal a partir de la senal*/
			/* para sitios donde no hay sig2str*/
    int i;
    for (i=0; sigstrnum[i].nombre!=NULL; i++) {
        if (sen == sigstrnum[i].senal) {
            return sigstrnum[i].nombre;
        }
    }
    return ("SIGUNKNOWN");
}

void detectProgram() {

}