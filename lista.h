/*
    Login: a.becerra
    Login: adrian.rego
    Nombre: Alejandro Becerra Suarez
    Nombre: Adrián Rego Criado
*/
#ifndef SHELL_C_lista_H
#define SHELL_C_lista_H

#include "cabeceras.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include <stdbool.h>

typedef struct node *lista;
typedef struct node *pos;

lista createEmptyList();             // Crea una lista vacía
void insert(lista *L, void *name);   // Inserta un elemento al final de la lista
pos first(lista L);                  // Retorna el primer elemento
pos second(lista L);                 // Como es una lista con cabecera, retorna el segundo valor de la lista, que es el primero con información
pos next(lista L, pos p);            // Retorna el elemento siguiente al indicado en los parámetros
int at_end(lista L, pos p);          // Devuelve 1 si el elemento indicado es el último de la lista
void *get(lista L, pos p);           // Nos permite obtener la información del nodo especificado
int elementsNumber(lista L);         // Cuenta cuantos elementos hay en la lista
void deleteList(lista *L);           // Elimina la lista entera, incluyendo la cabecera
//pos prev(lista L,pos p);           // Retorna el elemento previo al indicado
bool isEmptyList(lista L);           // Comprueba si una lista está vacía o no
void recorrerDe0aN(lista L);

#endif //SHELL_C_lista_H
