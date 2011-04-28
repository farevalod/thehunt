#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "listaSeresVivos.c"
#include "progenitorC.c"
#include "progenitorH.c"
#include "progenitorP.c"

int main()
{
    srand( time(NULL) );
    struct Nodo *head = NULL;
    struct Nodo *temp = NULL;
    FILE *entrada = fopen("entrada.txt","r");
    if(entrada == NULL)
    {
        printf("ERROR: Archivo entrada.txt no existe.\n\n");
        printf("Se debe crear un archivo con datos para\n");
        printf("configurar el medio ambiente antes de ejecutar!\n");
        exit(1);
    }
    char tipo;  //Tipo de elemento a ingresar.
    int num;    //Cantidad de elemento a ingresar.
    int lim;    //Cantidad de elementos comidos para terminar el juego
    int i;
    struct Animal *p;
    while(fscanf(entrada,"%c",&tipo))
    {
        fscanf(entrada,"%d",&num);
        if(tipo=='*')
        {
            lim = num;
            break;
        }
        for(i=0;i<num;i++)
        {
            p = (struct Animal *)malloc(sizeof(struct Animal));
            if(tipo == 'c' || tipo == 'C')
                crearCarnivoro(&p);
            else if(tipo == 'h' || tipo == 'H')
                crearHerbivoro(&p);
            else if(tipo == 'p' || tipo == 'P')
                crearPlanta(&p);
            
            insert(&head,p);
        }
     }
    printf("Datos leidos correctamente.\n");
    fclose(entrada);
    temp = head;
    while(temp!=NULL)
    {
        tipo = temp->ptrAnimal->tipo;
        if(tipo == 'c' || tipo == 'C')
            printf("Carnivoro:%s\n",temp->ptrAnimal->pAnimalC->nombre);
        else if(tipo == 'h' || tipo == 'H')
            printf("Herbivoro:%s\n",temp->ptrAnimal->pAnimalH->nombre);
        else if(tipo == 'p' || tipo == 'P')
            printf("Planta:%s\n",temp->ptrAnimal->pPlanta->nombre);
        temp=temp->next;
    }
    return 0;
}
