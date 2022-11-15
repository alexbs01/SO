/*
    Login: a.becerra
    Login: adrian.rego
    Nombre: Alejandro Becerra Suarez
    Nombre: Adrián Rego Criado
*/
#include "cabeceras.h"
//#include <stdlib.h>

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
    /*return p->data;*/
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
    /*pos position;
    int cantidadElementos = 0;
    for(position = second(L); position->next != NULL; position = next(L, position)) {
        cantidadElementos++;
    }
    return cantidadElementos;*/
}

bool isEmptyList(lista L) {
    return L->next == NULL;
}

pos prev(lista L,pos p) {
    /*funci ́on Buscar Anterior ( x, L ) :
        p := L;
        mientras pˆ.Siguiente <> nil y pˆ.Siguienteˆ.Elemento <> x hacer
            p := pˆ.Siguiente;
        devolver p
    fin funci ́on*/

    pos q = L;
    while(q->next != NULL && q->next != p) {
        q = q->next;
    }

    return q;

    /*pos q;
    for(q = second(L); q -> next != p; q = next(L,q));
    return q;
    */
    /*pos q; // q es el elemento previo

    if(p == L) {
        return NULL;
    }
    else {
        for(q = L; q->next != p; q = q->next);
        // Mientras el siguiente elemento a q sea distinto al introducido, se seguirá ejecutando el bucle
        return q;
    }*/
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
        printf("\n Esta en el primer elemento de la lista.");

    } else if(p->next == NULL) { // Eliminado en la última posición
        for(i = (*L)->next; i->next->next != NULL; i = i->next);
        i->next = NULL;
        printf("\n Esta en al último elemento de la lista.");

    } else { // Eliminado de un elemento que no se encuentra en los del medio
        for(i = next(*L, *L); i->next != p; i = i->next);
        i->next = p->next;
        printf("\nEsta en el medio de la lista.");
    }

    //free(i);
    free(p);

    printf("\nSe hizo free correctamente");
    /*pos i = (*L)->next;
    if(p == i) { // Eliminado en la primera posición de la lista
        (*L)->next = p->next;
        printf("\n Esta en el primer elemento de la lista.");

    } else if(p->next == NULL) { // Eliminado en la última posición
        for(i = next(*L, *L); i->next->next != NULL; i = i->next);
        i->next = NULL;
        printf("\n Esta en al último elemento de la lista.");

    } else { // Eliminado de un elemento que no se encuentra en los extremos
        for(i = next(*L, *L); i->next != p; i = i->next);
        i->next = p->next;
        printf("\nEsta en el medio de la lista.");
    }

    free(i);
    free(p);

    printf("\nSe hizo free correctamente");
}*/



    /*pos q;

    if(at_end(*L, p)) {
        q = prev(*L, p);
        q->next = NULL;
        free(p);

    } else {
        q = p->next;
        p->data = q->data;
        p->next = q->next;
        p = q;

        free(p);

    }*/

    /*pos q = prev(*L, *p);
    if(!at_end(*L, q)) {
        pos tmp = q->next;
        q->next = tmp->next;
        free(tmp);
    }*/
    /*
        p := Buscar Anterior ( x, L );
        si  ́Ultimo Elemento ( p ) entonces error No encontrado
        sino tmp := pˆ.Siguiente;
            pˆ.Siguiente := tmpˆ.Siguiente;
            liberar ( tmp )
     */

}
