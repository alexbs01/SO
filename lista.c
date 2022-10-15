/*
    Login: a.becerra
    Login: adrian.rego
    Nombre: Alejandro Becerra Suarez
    Nombre: Adrián Rego Criado
*/
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
    return p;
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
    for(position = second(L); position->next != NULL; position = next(L, position)) {
        cantidadElementos++;
    }
    return cantidadElementos;
}

bool isEmptyList(lista L) {
    return L == NULL;
}

/*pos prev(lista L,pos p) {
    pos q;
    for(q = first(L); q -> next != p; q = next(L,q)) {
    }
    return q;
}
*/

void deleteList(lista *L) {
    pos p;

    while(!isEmptyList(*L)) {
        p = *L;
        *L = (*L)->next;
        free(p);
    }
}
