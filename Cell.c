#include "Cell.h"
#include "listaSeresVivos.h"

int initMatrix(struct Cell matrix[8][8])
{
    int i, j;
    for(i=0;i<8;i++)
        for(j=0;j<8;j++)
        {
            matrix[i][j].entidad = NULL;
            matrix[i][j].xpos = 1+i*3;
            matrix[i][j].ypos = 3+j*6;
        }
    return 0;
}

int delCell(struct Cell *c)
{
    if(c->entidad != NULL)
    {
        switch(c->entidad->tipo)
        {
            case 'c':
            {
                free(c->entidad->pAnimalC);
                break;
            }
            case 'h':
            {
                free(c->entidad->pAnimalH);
                break;
            }
            case 'p':
            {
                free(c->entidad->pPlanta);
                break;
            }
        }
    }
    free(c->entidad);
    return 0;
}

int makeCell(struct Cell *c, struct Nodo **cList, struct Nodo **hList, struct Nodo **pList)
{
    struct Animal *temp;
    //ENTITY SPAWN PROBABILITY
    int pC = 98, pH = 97, pP = 96;
    int roll = (rand()%100);
    
    if((roll > pC)? 1 : 0)
    {
        pop(cList,&temp);
        c->entidad = temp;
        return 1;
    }
    if((roll > pH)? 1 : 0)
    {
        pop(hList,&temp);
        c->entidad = temp;
        return 1;
    }
    if((roll > pP)? 1 : 0)
    {
        pop(pList,&temp);
        c->entidad = temp;
        return 1;
    }
    c->entidad = NULL;
    return 0;
}

int apply(struct Cell matrix[8][8], struct Nodo **cList, struct Nodo **hList, struct Nodo **pList, char dir)
{
    int i, j;
            switch(dir)
            {
                case 'r':
                {
                    for(i=0;i<8;i++)
                    {
                        matrix[i][0].entidad = NULL;
                    }
                    for(i=0;i<8;i++)
                    {
                        for(j=0;j<7;j++)
                        {
                            matrix[i][j].entidad = matrix[i][j+1].entidad;
                        }
                        makeCell(&matrix[i][7],cList,hList,pList);
                    } 
                    break;
                }
                case 'l':
                {
                    for(i=0;i<8;i++)
                    {
                        matrix[i][7].entidad = NULL;
                    }
                    for(i=0;i<8;i++)
                    {
                        for(j=7;j>0;j--)
                        {
                            matrix[i][j].entidad = matrix[i][j-1].entidad;
                        }
                        makeCell(&matrix[i][0],cList,hList,pList);
                    }
                    break;
                    
                }
                case 'u':
                {
                    for(j=0;j<8;j++)
                    {
                        matrix[7][j].entidad = NULL;
                    }
                    for(j=0;j<8;j++)
                    {
                        for(i=7;i>0;i--)
                        {
                            matrix[i][j].entidad = matrix[i-1][j].entidad;
                        }
                        makeCell(&matrix[0][j],cList,hList,pList);
                    }
                    break;
                }
                case 'd':
                {
                    for(j=0;j<8;j++)
                    {
                        matrix[0][j].entidad = NULL;
                    }
                    for(j=0;j<8;j++)
                    {
                        for(i=0;i<7;i++)
                        {
                            matrix[i][j].entidad = matrix[i+1][j].entidad;
                        }
                        makeCell(&matrix[7][j],cList,hList,pList);
                    }
                    break;
                }
            }
            return 0;
}
