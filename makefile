all:main

lista.o: lista.c lista.h cabeceras.h
	gcc -c lista.c

funcionesAuxiliares.o: funcionesAuxiliares.c funcionesAuxiliares.h cabeceras.h
	gcc -c funcionesAuxiliares.c

comandos.o: comandos.c comandos.h cabeceras.h
	gcc -c comandos.c

main.o: main.c lista.h funcionesAuxiliares.h cabeceras.h
	gcc -c main.c

main: main.o lista.o funcionesAuxiliares.o comandos.c cabeceras.h
	gcc -o p0 main.o lista.o funcionesAuxiliares.o comandos.c

clean:
	rm -f shell.o list.o shell


