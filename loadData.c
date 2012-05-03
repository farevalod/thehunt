#include "listaSeresVivos.c"
#include "progenitorC.c"
#include "progenitorH.c"
#include "progenitorP.c"

int loadData(struct Nodo **cList, struct Nodo **hList, struct Nodo **pList)
{
    FILE *entrada = fopen("entrada.txt","r");
    if(!entrada)
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
			if(tipo=='c'||tipo=='C')
            {
                crearCarnivoro(&p,0);
                insert(cList,p);
            }
			else if(tipo=='h'||tipo=='H')
            {
                crearHerbivoro(&p,0);
                insert(hList,p);
            }
            else if(tipo == 'p' || tipo == 'P')
            {
                crearPlanta(&p);
                insert(pList,p);
            }
        }
     }
    fclose(entrada);
    return lim;
}
