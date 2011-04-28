#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaSeresVivos.c"
#include "progenitorC.c"
#include "progenitorH.c"
#include "progenitorP.c"

int main()
{
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
                crearCarnivoro(&p,"CarnivoroPrueba",100,5);//TODO: Funciones de nombre, hp y atk random.
            else if(tipo == 'h' || tipo == 'H')
                crearHerbivoro(&p,"HerviboroPrueba",12,1,2);//TODO: Funciones random de nombre, hp, def y mov
            else if(tipo == 'p' || tipo == 'P')
                crearPlanta(&p,"PlantaPrueba",2);//TODO; Función random nombre y turnos.
            
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
            printf("prueba:%s\n",temp->ptrAnimal->pAnimalC->nombre);
        else if(tipo == 'h' || tipo == 'H')
            printf("prueba:%s\n",temp->ptrAnimal->pAnimalH->nombre);
        else if(tipo == 'p' || tipo == 'P')
            printf("prueba:%s\n",temp->ptrAnimal->pPlanta->nombre);
        temp=temp->next;
    }
    return 0;
}
