//
// Created by alexb on 09/09/2022.
//
#include <stdlib.h>

struct node{
    void *data;
    struct node *next;
};

#include "lista.h"

list createEmptyList() {
    struct node *node = malloc(sizeof(struct node));
    node->next = NULL;

    return node;
}

void insert(list L, void *data) {
    struct node *node = L;
    while(node->next != NULL) {
        node = node->next;
    }
    node->next = malloc(sizeof(struct node));
    node->next->next = NULL;
    node->next->data = data;
}

pos first(list L) {
    return L;
}

pos second(list L) {
    return L->next;
}

pos next(list L, pos p) {
    if(p->next != NULL) {
        return p->next;
    }
    return p;
}

int at_end(list L, pos p) {
    return p->next == NULL;
}

void *get(list L, pos p) {
    if(p->next != NULL) {
        return p->next->data;
    }
    return NULL;
}
