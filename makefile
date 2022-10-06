all:main

lista.o: lista.c lista.h
	gcc -c lista.c

main.o: main.c lista.h funcionesAuxiliares.h
	gcc -c main.c

comandos.o: comandos.c comandos.h
	gcc -c comandos.c

funcionesAuxiliares.o: funcionesAuxiliares.c funcionesAuxiliares.h
	gcc -c funcionesAuxiliares.c

main: main.o lista.o funcionesAuxiliares.o comandos.c
	gcc -o p0 -Wall main.o lista.o funcionesAuxiliares.o comandos.c

clean:
	rm -f shell.o list.o shell


