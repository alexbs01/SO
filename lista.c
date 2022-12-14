/*
    Login: a.becerra
    Login: adrian.rego
    Nombre: Alejandro Becerra Suarez
    Nombre: Adrián Rego Criado
*/
#include "cabeceras.h"
#include <stdlib.h>

struct node{
    void *data;
    struct node *next;
};

#include "lista.h"

lista createEmptyList() {
    struct node *node = malloc(sizeof(struct node));
    node->next = NULL;

    return node;
}

void insert(lista *L, void *data) {
    struct node *node = *L;

    while(node->next != NULL) {
        node = node->next;
    }

    node->next = malloc(sizeof(struct node));
    node->next->next = NULL;
    node->next->data = data;
}

pos first(lista L) {
    return L;
}

pos second(lista L) {
    return L->next;
}

pos next(lista L, pos p) {
    if(p->next != NULL) {
        return p->next;
    }

    return NULL;
}

int at_end(lista L, pos p) {
    return p->next == NULL;
}

void *get(lista L, pos p) {
    if(p->next != NULL) {
        return p->next->data;
    }

    return NULL;
}

int elementsNumber(lista L) {
    pos position;
    int cantidadElementos = 0;

    for(position = L; position->next != NULL; position = position->next) {
        cantidadElementos++;
    }

    return cantidadElementos;
}

bool isEmptyList(lista L) {
    return L->next == NULL;
}

pos prev(lista L,pos p) {
    pos q = L;

    while(q->next != NULL && q->next != p) {
        q = q->next;
    }

    return q;
}


void deleteList(lista *L, void (* freedata)(void *)) {
    pos p = (*L)->next;
    pos q;

    while(p != NULL) {
        q = p;
        freedata(p->data);
        p = p->next;
        free(q);
    }

    free(*L);
}

pos find(lista L, void *p) {
    pos position;
    for(position = second(L); position->next != NULL && position != p; position = next(L, position));

    return position;
}

void deleteAtPosition(lista *L, pos p) {
    p = p->next;
    pos i;

    if(p == (*L)->next) { // Eliminado en la primera posición de la lista
        (*L)->next = (*L)->next->next;

    } else if(p->next == NULL) { // Eliminado en la última posición
        for(i = (*L)->next; i->next->next != NULL; i = i->next);
        i->next = NULL;

    } else { // Eliminado de un elemento que no se encuentra en los del medio
        for(i = next(*L, *L); i->next != p; i = i->next);
        i->next = p->next;
    }

    free(p->data);
    free(p);
    /*pos q;
    if(p->next == NULL) { // Eliminado en la última posición
        for(q = *L; q->next->next != NULL; q = q->next);
        q->next = NULL;

    } else { // Eliminado de un elemento que no se encuentra en los extremos
        q = p->next;
        p->data = q->data;
        p->next = q->next;
        p = q;
    }

    free(p);*/



    printf("\nSe hizo liberó memoria correctamente");
}
