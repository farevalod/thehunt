/* SampleApplication.c - A C Program using the LinkedList class */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaSeresVivos.c"
#include "progenitorC.c"
#include "progenitorH.c"

int main()
{
    struct Nodo *head = NULL;
    struct Nodo *temp = NULL;
    
    struct Animal *p1 = (struct Animal *)malloc(sizeof(struct Animal));
    char name1[20] = "Puma Salvaje";
    crearCarnivoro(&p1,name1,100,5); //puntero, nombre, hp, ataque.
    insert(&head,p1);
    
    struct Animal *p2 = (struct Animal *)malloc(sizeof(struct Animal));
    char name2[20] = "Conejo";
    crearHerbivoro(&p2,name2,12,1,2);
    insert(&head,p2);

    temp = head;
    while(temp!=NULL)
    {
        if(temp->ptrAnimal->pAnimalC != NULL)
            printf("prueba:%s\n",temp->ptrAnimal->pAnimalC->nombre);
        else
            printf("prueba:%s\n",temp->ptrAnimal->pAnimalH->nombre);
        temp=temp->next;
    }
    return 0;
}
