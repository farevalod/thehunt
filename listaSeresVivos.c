/******** Archivo: listaEnlazada.c ********************
Descripcion:    Implementación de la lista enlazada.
Funciones:      void insert(struct Nodo **head, void *ptrAnimal)
************************************************/

#include <malloc.h>
#include <stdio.h>
#include "listaSeresVivos.h"

/******** Funcion: insert ********
Descripcion: Inserta un nodo en la lista enlazada.
Parametros: 
    struct Nodo **head: Cabecera de la lista. Puede ser NULL.
    void *ptrAnimal:    Puntero a la estructura Animal con los
                        datos de la entidad. (Ya creado)
Retorno: void. Modifica la lista que recibe apuntada por head.
************************************************/

void insert(struct Nodo **head, void *ptrAnimal)
{
    struct Nodo *top;
    struct Nodo *newNode;
    newNode = (struct Nodo *)(malloc(sizeof(struct Nodo)));
    if(newNode == NULL)
    {
        printf("ERROR: malloc devuelve puntero NULL.\n");
        printf("Posible causa: OOM\n");
        return;
    }
    newNode->ptrAnimal = (struct Animal*)ptrAnimal; //Se enlaza la entidad al nodo.
    newNode->next = NULL;
    if(*head==NULL)         //Lista vacía: El nodo nuevo es la cabecera.
    {
        *head = newNode;
        return;
    }
    top = *head;
    while(top->next!=NULL)  //Lista no-vacía: Se recorre hasta el final
        top=top->next;
    top->next=newNode;      //Y se agrega el nuevo nodo.
    return;
}

void pop(struct Nodo **head, struct Animal **ret)
{
    if(*head == NULL)
    {
        //printf("ERROR: pop() a lista vacia!\n");
        ret = NULL;
        return;
    }
    *ret = (*head)->ptrAnimal;
    *head = (*head)->next;
    return;
}
        
