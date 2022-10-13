#include <stdio.h>
#include <stdlib.h>
#include "funcionesAuxiliares.h"
#include "comandos.h"
#include "cabeceras.h"
#include "lista.h"

int autores(char *tokens[], int ntokens, lista *lista) {
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

int pid(char *tokens[], int ntokens, lista *lista) {
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

int carpeta(char *tokens[], int ntokens, lista *lista) {
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

int fecha(char *tokens[], int ntokens, lista *lista) {
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

int hist(char *tokens[], int ntokens, lista *lista) {
    int position = 1;

    if(ntokens == 1) {  //Miramos si hist viene acompañado de un comando entre [] o no

        int numero = atoi(tokens[0]) * -1; // Sacamos el número introducido y lo volvemos positivo

        if(strcmp(tokens[0], "-c") == 0  ) {    //Si hay [-c] se borrará la lista que guarda el historial de comandos.
            deleteList(lista);

        } else if(numero > 0 && numero < elementsNumber(*lista)) { // Coprobamos que el número esté dentro del número de elementos del historial

            int contador = 1;
            pos p;

            for(p = second(*lista); contador != numero+1; p = next(*lista, p)) {
                struct histData *info = get(*lista, p);
                printf("%d-> %s", contador, info->command); // Mostramos los N primeros comandos
                contador++;
            }

        }

    } else if(ntokens == 0) { // Si hist no viene acompañado de [-c] o [-N] se mostrará por pantalla toda la lista de comandos usada.
        for(pos p = second(*lista); !at_end(*lista, p); p = next(*lista, p)) {
            struct histData *info = get(*lista, p);
            printf("%d-> %s", position, info->command); // Mostramos los comandos desde el primero al último
            position++;
        }

    } else {
        printf("Número incorrecto de parámetros aceptados por la función hist.");  //Si han puesto mas comandos entre corchetes que uno, se mostrara que ese comando no existe.
    }

    return 0;
}

int comando(char *tokens[], int ntokens, lista *lista) {

    if(ntokens == 1) {

        int numero = atoi(tokens[0]) * -1; // El número introducido lo volvemos positivo
        int contador = 1;

        if(numero > 0 && numero < elementsNumber(*lista)) {
            pos position;

            for(position = second(*lista); contador != numero; position = next(*lista, position)) {
                contador++; // Guardamos en position, el comando que estamos buscando
            }

            struct histData *command = get(*lista, position);
            char *tokensHist[MAX_TOKENS];
            int numeroTokens = splitString(command->command, tokensHist);
            processInput(tokensHist, numeroTokens, lista); // Con el comando encontrado, los procesamos para ejecutarlo

        } else {
            printf("Se debe insertar un número mayor a 0 como parámetro");
        }
    } else {
        printf("El comando \"comando\" debe llevar una parámetro del tipo -N, donde N es un número\n"
               "Mira el historial con el comando \"hist\" para saber que comandos puedes ejecutar");
    }

    return 0;
}

int infosis(char *tokens[], int ntokens, lista *lista) {
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



int fin(char *tokens[], int ntokens, lista *lista) { // Función para acabar la ejecución del programa, hace que se devuelva 1
    return 1;
}

int salir(char *tokens[], int ntokens, lista *lista) { // Función para acabar la ejecución del programa, hace que se devuelva 1
    return 1;
}

int bye(char *tokens[], int ntokens, lista *lista) { // Función para acabar la ejecución del programa, hace que se devuelva 1
    return 1;
}

int create(char *tokens[], int ntokens, lista *lista) {
    int errorNumber;

    if(ntokens == 1) {
        errorNumber = mkdir(tokens[0], 0771); // Se crea la carpeta con permisos rwxrwx--x, y se guarda el número de error

        if(errorNumber == -1) { // Si hay número de error es que no se pudo crear la carpeta
            printf("No se pudo crear %s: %s", tokens[0], strerror(errno));

        } else {
            printf("Se creo la carpeta; %s", tokens[0]);

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

off_t tamanoFichero(char *file) {     //Returns size of one file
    struct stat size;

    if(stat(file,&size) == -1) {
        return -1;
    }

    return size.st_size;
}

int printStat(char *tokens, SStatCommand *flags) {
    char fecha[MAX_LENGTH];
    struct tm fechaYHora;
    char formatoFechaYHora[] = "%Y/%m/%d-%H:%M";
    struct stat datos; // número de links, número de inodos y tamaño del archivo
    struct passwd *usuario; // El struct passwd, contiene información del usuario
    struct group *grupo; // El struct group, contiene información del grupo
    char *permisos; // Los permisos si no tienen valor tienen un guion
    char linkSimbolico[MAX_LENGTH];
    //char *archivo = basename(tokens);

    if(!flags->longFlag) {
        long espacio = tamanoFichero(tokens);
        if(espacio == -1) {
            return -1;
        } else {
            printf("%ld\t%s\n", espacio, tokens);
        }
    } else {
        (flags->accFlag)? (localtime_r(&datos.st_atime, &fechaYHora)) : (localtime_r(&datos.st_mtime, &fechaYHora));

        if(lstat(tokens, &datos) == -1) {
            return 1;
        }

        usuario = getpwuid(datos.st_uid);
        grupo = getgrgid(datos.st_gid);
        permisos = ConvierteModo2(datos.st_mode);

        strftime(fecha, MAX_LENGTH, formatoFechaYHora, &fechaYHora);
        printf("%s\t%ld \t(%8ld)\t%s\t%s\t%s\t%ld %s", fecha,
               datos.st_nlink,
               datos.st_ino,
               usuario->pw_name,
               grupo->gr_name,
               permisos,
               datos.st_size,
               tokens);

        // Si el flag de links simbólicos y la función readlink dan true, mostrará el link
        // Cuando readlink falla retorna un -1
        if(flags->linkFlag && (readlink(tokens, linkSimbolico, MAX_LENGTH) != -1)) {
            printf(" --> %s\n", linkSimbolico);

        } else {
            printf("\n");

        }

    }
    return 0;
}

int stats(char *tokens[], int ntokens, lista *lista) {
    SStatCommand flags = {false, false, false};
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

        for(int i = numberFlags - 1; i < ntokens; i++) {
            printStat(tokens[i], &flags);
        }

    }
    return 0;
}



//**********************************************************************************************************************
/*
int printFileInfo(char *path, struct listOptions *com) {   //Shows one file's info
    struct stat s;
    struct group *grp;
    struct passwd *pwd;
    char fechaOut [MAX_LENGTH];
    char *permisos = "---------- ";
    struct tm lt;
    char symlink[MAX_LENGTH] = "";
    char *file = basename(path);

    if(lstat(path,&s)==-1) return -1;

    permisos = ConvierteModo2(s.st_mode);

    if (!com->lng){ //Basic listing
        long size;
        if((size=tamanoFichero(path))==-1) return -1;
        else printf("%ld\t%s\n", size, file);
    }else{ //Long listing
        if((pwd = getpwuid(s.st_uid)) == NULL) return -1;
        if((grp = getgrgid(s.st_gid)) == NULL) return -1;

        if(com->acc) localtime_r(&s.st_atime, &lt);
        else localtime_r(&s.st_mtime, &lt);

        // YY/MM/DD-hh:mm
        strftime(fechaOut, MAX_LENGTH, "%Y/%m/%d-%H:%M", &lt);

        printf("%s%4ld ( %ld)\t%s\t%s\t%s%9ld %s", fechaOut, s.st_nlink, s.st_ino,
                pwd->pw_name, grp->gr_name, permisos, s.st_size, file) ;
        if(com->link && (readlink(path, symlink, MAX_LENGTH)!=-1))
            printf(" -> %s\n", symlink);
        else printf("\n");
    }
    return 0;
}


int isDir(const char *path) {
    struct stat s;
    stat(path, &s);
    int out = S_ISDIR(s.st_mode);
    return out;
}

int listSubDir(char *dir, struct listOptions *com) {
    DIR *dirp;
    struct dirent *flist;
    char aux[MAX_LENGTH];

    if ((dirp=opendir(dir)) == NULL) return -1;
    while ((flist=readdir(dirp))!= NULL) { //recorre los archivos en el directorio

        if (!com->hid && flist->d_name[0] == '.') continue;   //If "hid" option is off, we ignore
        if (strcmp(flist->d_name, "..") == 0 ||              // files that start with ".." or "."
            strcmp(flist->d_name, ".") == 0)continue;

        strcpy(aux, dir);
        strcat(strcat(aux, "/"),flist->d_name);
        if (isDir(aux)) {
            printDirInfo(aux, com);
        }
    }
    closedir(dirp);
    return 0;
}

int printDirInfo(char *dir, struct listOptions *com) {  //Shows one directory's information
    DIR *dirp;
    struct dirent *flist;
    char aux[MAX_LENGTH];

    if (com->recb) {
        if(listSubDir(dir, com)) return -1;
    }
    if((dirp = opendir(dir)) == NULL) return -1;

    printf("✦****** %s ******✦\n",dir);
    while ((flist=readdir(dirp)) != NULL) { // Recorre los archivos en el directorio
        strcpy(aux, dir);
        strcat(strcat(aux, "/"),flist->d_name);

        if(!com->hid && flist->d_name[0] == '.') continue;

        if(printFileInfo(aux, com)) return -1;
    }
    closedir(dirp);

    if(!com->recb && com->reca){            //recb has priority over reca
        if(listSubDir(dir, com)) return -1;
    }
    return 0;
}
*/

/*
int list(char *tokens[], int ntokens, lista *lista) {
    char msgError[] = "Error de lectura"; //Mensaje de error.

    if (ntokens != 0) {

        struct listOptions com = {0,0,0,0,0,0};

        for (int cnt = 0; cnt < ntokens; cnt++) {
            if (strcmp(tokens[cnt], "-acc") == 0)         com.acc = 1;
            else if (strcmp(tokens[cnt], "-hid") == 0)    com.hid = 1;
            else if (strcmp(tokens[cnt], "-link") == 0)   com.link = 1;
            else if (strcmp(tokens[cnt], "-lng") == 0)    com.lng = 1;
            else if (strcmp(tokens[cnt], "-reca") == 0)   com.reca = 1;
            else if (strcmp(tokens[cnt], "-recb") == 0)   com.recb = 1;
        }

        int cnt = (com.acc + com.hid + com.link + com.lng + com.reca + com.recb);

        if (cnt == ntokens) {
            carpeta(0,0,lista); //si no existe parametro a listar
        }

        while (cnt < ntokens) {
            if (printDirInfo(tokens[cnt], &com) == (-1)) {
                perror(msgError); // Mostramos mensaje de error.
            }
            cnt++;
        }
    } else {
        carpeta(0,0,lista); // Muestra el directorio actual.
    }

    return 0;
}
*/

/*#include <dirent.h>  se necesita si queremos recuperar este list*/
int list(char *tokens[], int ntokens, lista *lista) {/*
    char path[MAX_LENGTH]; // Creamos un array de caracteres para guardar la dirección del directorio a saber
    struct stat sb;

    if (ntokens == 0) { // Si el usuario no introduce un directorio ejecutamos list sobre el actual.
        if (getcwd(path, sizeof(path)) == NULL) { // Si no falla se guarda en path la dirección del directorio actual.
            perror("getcwd() error"); // Si falla la función para conseguir la ruta del directorio se muestra un mensaje de error.
            return 1;
        }

    } else if (ntokens == 1) { // Si el usuario introduce un directorio ejecutamos list sobre ese.
        strncpy(path, tokens[0], sizeof(*tokens) - 1); // Se guarda en path la dirección del directorio dado.
        path[sizeof(*tokens) - 1] = '\0';
    }

    DIR *d;
    struct dirent *dir;

    d = opendir(path); // Abrir directorio y guardarlo en la variable d.

    if(d) {
        while((dir = readdir(d)) != NULL) {              // Vamos mostrando por salida cada cosa almacenada en el directorio hasta que no haya nada más.
            stat((char*) d, &sb);
            if (dir-> d_type != DT_DIR) {                     // Si no es directorio que lo muestre de color azul.
                printf("%10ld %s\n", sb.st_size, dir->d_name); // //AÑADIR EL PESO DEL DIRECTORIO
            } else if (dir -> d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0 ) { // No se mostrarán el contenido de directorios posteriores o anteriores al dado.
                printf("%10ld %s\n", sb.st_size, dir->d_name);  // Si es un directorio lo muestra en verde.
            }
        }
        closedir(d);
    }
*/
    return 0;
}

int delete(char *tokens[], int ntokens, lista *lista) {

    return 0;
}

int deltree(char *tokens[], int ntokens, lista *lista) {

    return 0;
}