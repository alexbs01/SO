/*
    Login: a.becerra
    Login: adrian.rego
    Nombre: Alejandro Becerra Suarez
    Nombre: Adrián Rego Criado
*/
#include <stdio.h>
#include "funcionesAuxiliares.h"
#include "lista.h"
#include "cabeceras.h"

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
    int (*cmdFunction)(char *tokens[], int ntokens, lista *listas); // Nombre de la función y sus parámetros
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
        {NULL, NULL}
};

int processInput(char *tokens[], int ntokens, lista *lista) {
    int exit = 0;

    for(int i = 0; cmds[i].cmdName != NULL; i++) { // Se busca el nombre del comando en el struct de arriba
        if(strcmp(tokens[0], cmds[i].cmdName) == 0) {
            exit = cmds[i].cmdFunction(tokens + 1, ntokens - 1, lista); // Cuando se encuentra se ejecuta la función asociada
            return exit;
        }
    }

    printf("Comando no encontrado");
    return exit;
}

// Se hace el mismo proceso que con processInput, pero se muestra por pantalla lo almacenado en ayudaCmd
int ayuda(char *tokens[], int ntokens, lista *lista) {
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

off_t tamanoFichero(char *file) {     //Returns size of one file
    struct stat size;

    if(stat(file,&size) == -1) {
        return -1;
    }

    return size.st_size;
}

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

    if(!flags.longFlag) {
        if(espacio == -1) {
            return -1;
        }

        printf("%ld\t%s\n", espacio, tokens);

    } else {
        (flags.accFlag)? (localtime_r(&datos.st_atime, &fechaYHora)) : (localtime_r(&datos.st_mtime, &fechaYHora));

        if(lstat(tokens, &datos) == -1) { // Carga en datos la información del archivo
            return 1;
        }

        usuario = getpwuid(datos.st_uid);
        grupo = getgrgid(datos.st_gid);
        permisos = ConvierteModo2(datos.st_mode);

        strftime(fecha, MAX_LENGTH, formatoFechaYHora, &fechaYHora);
        printf("%s\t%ld \t(%8ld)\t%s    \t%s    \t%s\t%ld\t\t%s", fecha,
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
            printf(" --> %s\n", linkSimbolico);

        } else {
            printf("\n");

        }


    }


    return 0;
}

int isDirectory(char *tokens) {
    struct stat st;
    stat(tokens, &st);

    int isDirectory = S_ISDIR(st.st_mode);
    return isDirectory;
}

int delete_item(char *path) {
    char nuevaRuta[MAX_LENGTH];
    DIR *directorio;
    struct dirent *entrada;

    if((directorio = opendir(path)) == NULL) {
        return -1;
    }

    while((entrada = readdir(directorio)) != NULL) {
        strcpy(nuevaRuta, path);
        strcat(strcat(nuevaRuta, "/"),entrada->d_name);

        if(strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0) {
            continue;
        }

        if(isDirectory(nuevaRuta)) {
            delete_item(nuevaRuta);
        }

        if(remove(nuevaRuta)) {
            return -1;
        }

    }
    closedir(directorio);

    return 0;
}

int recAyB(char *path, SStatListCommand flags) {
    char nuevaRuta[MAX_LENGTH];
    DIR *directorio;
    struct dirent *entrada;

    if((directorio = opendir(path)) == NULL) {
        return -1;
    }

    printf("*** %s\n", path);

    while((entrada = readdir(directorio)) != NULL && strcmp(&entrada->d_name[0], ".") != 0) {

        if(strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0) {
            continue;
        }

        strcpy(nuevaRuta, path);
        strcat(strcat(nuevaRuta, "/"),entrada->d_name);

        if(flags.recbFlag) {
            recAyB(nuevaRuta, flags);
        }

        printStatAndList(nuevaRuta, flags);

        if(flags.recaFlag) {
            recAyB(nuevaRuta, flags);
        }
    }

    closedir(directorio);

    return 0;
}

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

lista listaArbolCarpetas(lista *L, char *path, SStatListCommand flags) {
    struct stat st;
    char nuevaRuta[MAX_LENGTH];
    DIR *directorio;
    struct dirent *entrada;
    char nuevaEntrada[MAX_LENGTH];
//// Si no se tienen permisos para acceder a la carpeta, colapsa
    //directorio = opendir(path);

    if((directorio = opendir(path)) != NULL) {
        while((entrada = readdir(directorio)) != NULL) {
            if(strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0) {
                continue;
            }
            if(strcmp(path, "/") == 0) {
                strcat(strcpy(nuevaRuta, "/"),entrada->d_name);
            } else {
                strcpy(nuevaRuta, path);
                strcat(strcat(nuevaRuta, "/"),entrada->d_name);
            }

            //printf("Nueva Ruta: %s\n", nuevaRuta);
            // printf("d_name: %s\n", entrada->d_name);


            if(isDirectory(nuevaRuta)) {
                strcpy(nuevaEntrada, entrada->d_name);
                //printf("d_name: %c\n", nuevaEntrada[0]);

                if(nuevaEntrada[0] != '.') {
                    //insert(L, nuevaRuta);
                    if(flags.recbFlag) listaArbolCarpetas(L, nuevaRuta, flags);
                    printf("Nueva ruta: %s\n", nuevaRuta);
                    printStatAndList(nuevaRuta, flags);
                    if(flags.recaFlag) listaArbolCarpetas(L, nuevaRuta, flags);
                    
                }

            }

        }
    }

    closedir(directorio);

    return *L;
}

int recursivaA(lista L, SStatListCommand flags) {
    int contador = 0;
    for(pos p = first(L); contador != elementsNumber(L); p = next(L, p)) {
        struct histData *path = get(L, p);
        printStatAndList(path->command, flags);
        contador++;
    }
    return 0;
}