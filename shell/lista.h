#ifndef SHELL_C_LISTA_H
#define SHELL_C_LISTA_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct node *list;
typedef struct node *pos;

list createEmptyList();             // Crea una lista vacía
void insert(list *L, void *name);   // Inserta un elemento al final de la lista
pos first(list L);                  // Retorna el primer elemento
pos second(list L);                 // Como es una lista con cabecera, retorna el segundo valor de la lista, que es el primero con información
pos next(list L, pos p);            // Retorna el elemento siguiente al indicado en los parámetros
int at_end(list L, pos p);          // Devuelve 1 si el elemento indicado es el último de la lista
void *get(list L, pos p);           // Nos permite obtener la información del nodo especificado
int elementsNumber(list L);         // Cuenta cuantos elementos hay en la lista
void deleteList(list *L);           // Elimina la lista entera, incluyendo la cabecera
//pos prev(list L,pos p);           // Retonrna el elemento previo al indicado
bool isEmptyList(list L);           // Comprueba si una lista está vacía o no

#endif //SHELL_C_LISTA_H
