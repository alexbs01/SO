EXECUTABLE = p1

all:main

funcionesAuxiliares.o: funcionesAuxiliares.c funcionesAuxiliares.h cabeceras.h
	gcc -c funcionesAuxiliares.c

comandos.o: comandos.c comandos.h cabeceras.h
	gcc -c comandos.c

lista.o: lista.c lista.h cabeceras.h
	gcc -c lista.c

$(EXECUTABLE).o: $(EXECUTABLE).c lista.h funcionesAuxiliares.h
	gcc -c $(EXECUTABLE).c

main: $(EXECUTABLE).o lista.o funcionesAuxiliares.o comandos.o cabeceras.h
	gcc -o $(EXECUTABLE) $(EXECUTABLE).o lista.o funcionesAuxiliares.o comandos.o

clean:
	rm -f lista.o funcionesAuxiliares.o comandos.o $(EXECUTABLE).o $(EXECUTABLE)


