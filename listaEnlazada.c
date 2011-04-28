/******** Archivo: listaEnlazada.c ********************
Descripcion:    Implementación de la lista enlazada.
Funciones:      void insert(struct Nodo **head, void *ptrAnimal )
************************************************/

#include <malloc.h>
#include <stdio.h>
#include "listaEnlazada.h"

void insert(struct Nodo **head, void *ptrAnimal )
{
    struct Nodo *top;
    struct Nodo *newNode;
    newNode = (struct Nodo *)(malloc(sizeof(struct Nodo)));
    newNode->ptrAnimal = (struct Animal*)ptrAnimal;
    newNode->next = NULL;
    if(*head==NULL)
    {
        *head = newNode;
        return;
    }
    top = *head;
    while(top->next!=NULL)
        top=top->next;
    top->next=newNode;
    return;
}

