#include "Cell.h"
#include "listaSeresVivos.h"
#include "AI.c"

extern WINDOW *msgs;

int initMatrix(struct Cell matrix[9][9])
{
    int i, j;
    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
        {
            matrix[i][j].entidad = NULL;
            matrix[i][j].xpos = 1+i*3;
            matrix[i][j].ypos = 3+j*6;
        }
    return 0;
}

int makeCell(struct Cell *c, struct Nodo **cList, struct Nodo **hList, struct Nodo **pList)
{
    struct Animal *temp;
    //ENTITY SPAWN PROBABILITY
    int pC = 98, pH = 97, pP = 95;
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

int iterateMatrix(struct Cell matrix[9][9], struct Animal *player)
{
    int i, j;
    char type;
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            if((matrix[i][j].entidad == NULL) || (matrix[i][j].entidad->tipo == 'p'))
                continue;
            if( (i != 4) || (j != 4) )
            {
                type = matrix[i][j].entidad->tipo;
                if(type == 'c')
                {
                    if(matrix[i][j].entidad->getHP(matrix[i][j].entidad) < 1)
                    {
                        matrix[i][j].entidad->die(matrix[i][j].entidad);    //Chao animal.
                    }
                    else
                        carnivoreAI(matrix,i,j,player);
                }
                if(type == 'h')
                {
                    if(matrix[i][j].entidad->getHP(matrix[i][j].entidad) < 1)
                    {
                        matrix[i][j].entidad->die(matrix[i][j].entidad);    //Chao animal.
                    }
                    else
                        herbivoreAI(matrix,i,j,player);
                }
                if(type == 'x')
                    if(matrix[i][j].entidad->eat(matrix[i][j].entidad,0) < 0)
                        matrix[i][j].entidad = NULL;
            }
        }
    }
    return 0;
}

int apply(struct Cell matrix[9][9], struct Animal *player, struct Nodo **cList, struct Nodo **hList, struct Nodo **pList, char dir)
{
    int i, j;
    switch(dir)
    {
        case 'r':
        {
            if(matrix[4][5].entidad == NULL) //Si no hay entidad, mover.
            {
                for(i=0;i<9;i++)
                {
                    matrix[i][0].entidad = NULL;
                }
                for(i=0;i<9;i++)
                {
                    for(j=0;j<8;j++)
                    {
                        if((i != 4) || (j != 4)) //El animal del jugador (en 4,4) no se mueve.
                            matrix[i][j].entidad = matrix[i][j+1].entidad;
                    }
                    makeCell(&matrix[i][8],cList,hList,pList);
                } 
                return 0;
            }
            else                    //SI HAY ALGO EN LA CELDA...
            {
                if(player->tipo == 'c')//Si el player es carnivoro...
                {                      //y hay un animal vivo...
                    if((matrix[4][5].entidad->tipo != 'x') && (matrix[4][5].entidad->tipo != 'p'))  
                    {                  //ATACAR
                        int dmg = (rand() % 12) * player->pAnimalC->ataque;
                        matrix[4][5].entidad->hitHP(matrix[4][5].entidad,dmg);
                        if(dmg > 0)
                            mvwprintw(msgs,2, 1,"Atacas al animal! Le haces %d HP de daño!          ",dmg);
                        else
                            mvwprintw(msgs,2, 1,"El animal esquiva tu intento de atacarlo.");
                        wrefresh(msgs);
                    }                  //Si no, comer:
                    else if(matrix[4][5].entidad->tipo == 'x') //Alimentarse de un cadaver.
                    {
                        int heal = (rand()%20);
                        player->hitHP(player,-heal);
                        matrix[4][5].entidad->eat(matrix[4][5].entidad,-1);
                        wattron(msgs,COLOR_PAIR(1));
                        mvwprintw(msgs,2, 1,"Te alimentas del cadaver. Recuperas %d HP!          ",heal);
                        mvwprintw(msgs,3, 1,"%s", "                                                       ");
                        wattroff(msgs,COLOR_PAIR(1));
                        wrefresh(msgs);
                        player->eat(player,1);
                    }
                    return 1;
                    //Si es una planta, retornar.
                }
                if(player->tipo == 'h')
                {
                    if(matrix[4][5].entidad->tipo == 'p') //Alimentarse de una planta.
                    {
                        int heal = (rand()%20);
                        player->hitHP(player,-heal);
                        wattron(msgs,COLOR_PAIR(1));
                        mvwprintw(msgs,2, 1,"Te alimentas de la %s. Recuperas %d HP!          ",matrix[4][5].entidad->pPlanta->nombre,heal);
                        mvwprintw(msgs,3, 1,"%s", "                                                       ");
                        wattroff(msgs,COLOR_PAIR(1));
                        wrefresh(msgs);
                        matrix[4][5].entidad = NULL;
                        player->eat(player,1);
                    }
                    return 0;
                }
                
            }
        }
        case 'l':
        {
            if(matrix[4][3].entidad == NULL) //Si no hay entidad, mover.
            {
                for(i=0;i<9;i++)
                {
                    matrix[i][8].entidad = NULL;
                }
                for(i=0;i<9;i++)
                {
                    for(j=8;j>0;j--)
                    {
                        if((i != 4) || (j != 4)) //El animal del jugador (en 4,4) no se mueve.
                            matrix[i][j].entidad = matrix[i][j-1].entidad;
                    }
                    makeCell(&matrix[i][0],cList,hList,pList);
                }
                return 0;
            }
            else                    //SI HAY ALGO EN LA CELDA...
            {
                if(player->tipo == 'c')//Si el player es carnivoro...
                {                      //y hay un animal vivo...
                    if((matrix[4][3].entidad->tipo != 'x') && (matrix[4][3].entidad->tipo != 'p'))  
                    {                  //ATACAR
                        int dmg = (rand() % 12) * player->pAnimalC->ataque;
                        matrix[4][3].entidad->hitHP(matrix[4][3].entidad,dmg);
                        if(dmg > 0)
                            mvwprintw(msgs,2, 1,"Atacas al animal! Le haces %d HP de daño!          ",dmg);
                        else
                            mvwprintw(msgs,2, 1,"El animal esquiva tu intento de atacarlo.");
                        wrefresh(msgs);
                    }                  //Si no, comer:
                    else if(matrix[4][3].entidad->tipo == 'x') //Alimentarse de un cadaver.
                    {
                        int heal = (rand()%20);
                        player->hitHP(player,-heal);
                        matrix[4][3].entidad->eat(matrix[4][3].entidad,-1);
                        wattron(msgs,COLOR_PAIR(1));
                        mvwprintw(msgs,2, 1,"Te alimentas del cadaver. Recuperas %d HP!          ",heal);
                        mvwprintw(msgs,3, 1,"%s", "                                                       ");
                        wattroff(msgs,COLOR_PAIR(1));
                        wrefresh(msgs);
                        player->eat(player,1);
                    }
                    return 1;
                    //Si es una planta, retornar.
                }
            }
            if(player->tipo == 'h')
            {
                if(matrix[4][3].entidad->tipo == 'p') //Alimentarse de una planta.
                {
                    int heal = (rand()%20);
                    player->hitHP(player,-heal);
                    wattron(msgs,COLOR_PAIR(1));
                    mvwprintw(msgs,2, 1,"Te alimentas de la %s. Recuperas %d HP!          ",matrix[4][3].entidad->pPlanta->nombre,heal);
                    mvwprintw(msgs,3, 1,"%s", "                                                       ");
                    wattroff(msgs,COLOR_PAIR(1));
                    wrefresh(msgs);
                    matrix[4][3].entidad = NULL;
                    player->eat(player,1);
                }
                return 0;
            }
            
        }
        case 'u':
        {
            if(matrix[3][4].entidad == NULL) //Si no hay entidad, mover.
            {
                for(j=0;j<9;j++)
                {
                    matrix[8][j].entidad = NULL;
                }
                for(j=0;j<9;j++)
                {
                    for(i=8;i>0;i--)
                    {
                        if((i != 4) || (j != 4)) //El animal del jugador (en 4,4) no se mueve.
                            matrix[i][j].entidad = matrix[i-1][j].entidad;
                    }
                    makeCell(&matrix[0][j],cList,hList,pList);
                }
                return 0;
            }
            else                    //SI HAY ALGO EN LA CELDA...
            {
                if(player->tipo == 'c')//Si el player es carnivoro...
                {                      //y hay un animal vivo...
                    if((matrix[3][4].entidad->tipo != 'x') && (matrix[3][4].entidad->tipo != 'p'))  
                    {                  //ATACAR
                        int dmg = (rand() % 12) * player->pAnimalC->ataque;
                        matrix[3][4].entidad->hitHP(matrix[3][4].entidad,dmg);
                        if(dmg > 0)
                            mvwprintw(msgs,2, 1,"Atacas al animal! Le haces %d HP de daño!          ",dmg);
                        else
                            mvwprintw(msgs,2, 1,"El animal esquiva tu intento de atacarlo.");
                        wrefresh(msgs);
                    }                  //Si no, comer:
                    else if(matrix[3][4].entidad->tipo == 'x') //Alimentarse de un cadaver.
                    {
                        int heal = (rand()%20);
                        player->hitHP(player,-heal);
                        matrix[3][4].entidad->eat(matrix[3][4].entidad,-1);
                        wattron(msgs,COLOR_PAIR(1));
                        mvwprintw(msgs,2, 1,"Te alimentas del cadaver. Recuperas %d HP!          ",heal);
                        mvwprintw(msgs,3, 1,"%s", "                                                       ");
                        wattroff(msgs,COLOR_PAIR(1));
                        wrefresh(msgs);
                        player->eat(player,1);
                    }
                    return 1;
                    //Si es una planta, retornar.
                }
            }
            if(player->tipo == 'h')
            {
                if(matrix[3][4].entidad->tipo == 'p') //Alimentarse de una planta.
                {
                    int heal = (rand()%20);
                    player->hitHP(player,-heal);
                    wattron(msgs,COLOR_PAIR(1));
                    mvwprintw(msgs,2, 1,"Te alimentas de la %s. Recuperas %d HP!          ",matrix[3][4].entidad->pPlanta->nombre,heal);
                    mvwprintw(msgs,3, 1,"%s", "                                                       ");
                    wattroff(msgs,COLOR_PAIR(1));
                    wrefresh(msgs);
                    matrix[3][4].entidad = NULL;
                    player->eat(player,1);
                }
                return 0;
            }
        }
        case 'd':
        {
            if(matrix[5][4].entidad == NULL) //Si no hay entidad, mover.
            {            
                for(j=0;j<9;j++)
                {
                    matrix[0][j].entidad = NULL;
                }
                for(j=0;j<9;j++)
                {
                    for(i=0;i<8;i++)
                    {
                        if((i != 4) || (j != 4)) //El animal del jugador (en 4,4) no se mueve.
                            matrix[i][j].entidad = matrix[i+1][j].entidad;
                    }
                    makeCell(&matrix[8][j],cList,hList,pList);
                }
                return 0;
            }
                        else                    //SI HAY ALGO EN LA CELDA...
            {
                if(player->tipo == 'c')//Si el player es carnivoro...
                {                      //y hay un animal vivo...
                    if((matrix[5][4].entidad->tipo != 'x') && (matrix[5][4].entidad->tipo != 'p'))  
                    {                  //ATACAR
                        int dmg = (rand() % 12) * player->pAnimalC->ataque;
                        matrix[5][4].entidad->hitHP(matrix[5][4].entidad,dmg);
                        if(dmg > 0)
                            mvwprintw(msgs,2, 1,"Atacas al animal! Le haces %d HP de daño!          ",dmg);
                        else
                            mvwprintw(msgs,2, 1,"El animal esquiva tu intento de atacarlo.");
                        wrefresh(msgs);
                    }                  //Si no, comer:
                    else if(matrix[5][4].entidad->tipo == 'x') //Alimentarse de un cadaver.
                    {
                        int heal = (rand()%20);
                        player->hitHP(player,-heal);
                        matrix[5][4].entidad->eat(matrix[5][4].entidad,-1);
                        wattron(msgs,COLOR_PAIR(1));
                        mvwprintw(msgs,2, 1,"Te alimentas del cadaver. Recuperas %d HP!          ",heal);
                        mvwprintw(msgs,3, 1,"%s", "                                                       ");
                        wattroff(msgs,COLOR_PAIR(1));
                        wrefresh(msgs);
                        player->eat(player,1);
                    }
                    return 1;
                    //Si es una planta, retornar.
                }
            }
            if(player->tipo == 'h')
            {
                if(matrix[5][4].entidad->tipo == 'p') //Alimentarse de una planta.
                {
                    int heal = (rand()%20);
                    player->hitHP(player,-heal);
                    wattron(msgs,COLOR_PAIR(1));
                    mvwprintw(msgs,2, 1,"Te alimentas de la %s. Recuperas %d HP!          ",matrix[5][4].entidad->pPlanta->nombre,heal);
                    mvwprintw(msgs,3, 1,"%s", "                                                       ");
                    wattroff(msgs,COLOR_PAIR(1));
                    wrefresh(msgs);
                    matrix[5][4].entidad = NULL;
                    player->eat(player,1);
                }
                return 0;
            }
        }
    }
    return 0;
}
