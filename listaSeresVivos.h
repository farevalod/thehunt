#include "progenitores.h"

struct Nodo{
    struct Nodo *next;          //Siguiente nodo en la lista.
    struct Animal *ptrAnimal;   //Puntero a estructura Animal.
};                              //En caso de ser un nodo vacío,
                                //ptrAnimal == NULL.
