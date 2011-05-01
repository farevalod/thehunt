#ifndef NODO_H
#define NODO_H

#include "progenitores.h"

struct Nodo
{
    struct Nodo *next;          //Siguiente nodo en la lista.
    struct Animal *ptrAnimal;   //Puntero a estructura Animal.
};                              //En caso de ser un nodo vacío,
                                //ptrAnimal == NULL.
                                
void insert(struct Nodo **head, void *ptrAnimal);
void pop(struct Nodo **head, struct Animal **ret);                               
#endif
