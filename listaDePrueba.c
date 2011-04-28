/* SampleApplication.c - A C Program using the LinkedList class */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaEnlazada.c"
int main()
{
    struct Nodo *head = NULL;
    struct Nodo *temp = NULL;
    
    struct AnimalCarnivoro *paC = (struct AnimalCarnivoro *)malloc(sizeof(struct AnimalCarnivoro));
    struct Animal *p1 = (struct Animal *)malloc(sizeof(struct Animal));
    char name1[20] = "Puma Salvaje";
    strcpy(paC->nombre,name1);
    paC->vida = 100;
    paC->nro_comidas = 0;
    paC->ataque = 5;
    p1->tipo = 'C';
    p1->pAnimalC = paC;   
    p1->pAnimalH = NULL;
    insert(&head,p1);
    
    struct AnimalHerbivoro *paH = (struct AnimalHerbivoro *)malloc(sizeof(struct AnimalHerbivoro));
    struct Animal *p2 = (struct Animal *)malloc(sizeof(struct Animal));
    char name2[20] = "Conejo";
    strcpy(paH->nombre,name2);
    paH->vida = 12;
    paH->nro_comidas = 0;
    paH->defensa = 1;
    paH->rand_mov = 2;
    p2->tipo = 'H';
    p2->pAnimalH = paH;   
    p2->pAnimalC = NULL;
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
