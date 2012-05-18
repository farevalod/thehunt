#include "Cell.h"
#include "listaSeresVivos.h"
#include "AI.c"

extern WINDOW *msgs;
extern char msg_buffer[5][55];

int initMatrix(struct Cell matrix[9][9])        //Se inicializan las coordenadas en pantalla
{                                               //para cada celda.
    int i, j;
    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
        {
            matrix[i][j].entidad = NULL;        //No hay entidaes cargadas por default.
            matrix[i][j].xpos = 1+i*3;
            matrix[i][j].ypos = 3+j*6;
        }
    return 0;
}

int makeCell(struct Cell *c, struct Nodo **cList, struct Nodo **hList, struct Nodo **pList)
{
    /*  1. Roll 1d100
        2. Si roll > p, cargar entidad en la celda c.
    */
    struct Animal *temp;
    //ENTITY SPAWN PROBABILITY
    int pC = 98, pH = 97, pP = 95;
    int roll = (rand()%100);
    
    if(roll > pC)
    {
        pop(cList,&temp);
        c->entidad = temp;
        return 1;
    }
    if(roll > pH)
	{
        pop(hList,&temp);
        c->entidad = temp;
        return 1;
    }
    if(roll > pP)
    {
        pop(pList,&temp);
        c->entidad = temp;
        return 1;
    }
    c->entidad = NULL;
    return 0;
}

int iterateMatrix(struct Cell matrix[9][9], struct Animal *player)
{   /*
        Llama a las funciones de AI, revisa los HP
        y las comidas restantes para los cadáveres.
    */
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
				if(matrix[i][j].entidad->getHP(matrix[i][j].entidad) < 1)
				{
					matrix[i][j].entidad->die(matrix[i][j].entidad);    //Chao animal.
				}
				else
				{
					if(type == 'c')
						carnivoreAI(matrix,i,j,player);
					else if(type == 'h')
						herbivoreAI(matrix,i,j,player);
				}
				if(type == 'x')
                    if(matrix[i][j].entidad->eat(matrix[i][j].entidad,0) < 1)
                        matrix[i][j].entidad = NULL;
            }
        }
    }
    return 0;
}
/*
	Esta función procesa el input del usuario.
	Para cada dirección:
		-Revisa si hay entidad en la casilla de destino:
			Si no hay, mueve
			Si hay entidad:
				y player carnívoro:
					animal vivo: atacarlo
					cadaver: alimentarse
				player herbivoro:
					planta: alimentarse

	La función es bastante larga, es un candidato principal
	para refactoring. Quizás sería posible abstraer funciones
	de ataque y alimentación.
*/
int apply(struct Cell matrix[9][9], struct Animal *player, struct Nodo **cList, struct Nodo **hList, struct Nodo **pList, char dir)
{   
    int i, j;
    char msg_string[55];
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
						if((i!=4)||(j!=4))//Elanimaldeljugador(en4,4)nosemueve.
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
                        int dmg = (rand() % 9) * player->pAnimalC->ataque;
                        matrix[4][5].entidad->hitHP(matrix[4][5].entidad,dmg);
                        if(dmg > 0)
                        {
                            sprintf(msg_string,"Atacas al animal! Le haces %d HP de daño!          ",dmg);
                            draw_msg(msg_string,msg_buffer);
                        }
                        else
                            draw_msg("El animal esquiva tu intento de atacarlo.",msg_buffer);
                    }                  //Si no, comer:
                    else if(matrix[4][5].entidad->tipo == 'x') //Alimentarse de un cadaver.
                    {
                        int heal = (rand()%10);
                        player->hitHP(player,-heal);
                        if(!matrix[4][5].entidad->eat(matrix[4][5].entidad,-1))
							matrix[4][5].entidad = NULL; //Eliminar cadaver cuando ya fue comido
                        wattron(msgs,COLOR_PAIR(1));
                        sprintf(msg_string,"Te alimentas del cadaver. Recuperas %d HP!          ",heal);
                        draw_msg(msg_string,msg_buffer);
                        wattroff(msgs,COLOR_PAIR(1));
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
                        sprintf(msg_string,"Te alimentas de la %s. Recuperas %d HP!          ",matrix[4][5].entidad->pPlanta->nombre,heal);
                        draw_msg(msg_string,msg_buffer);
                        wattroff(msgs,COLOR_PAIR(1));
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
						if((i!=4)||(j!=4))//Elanimaldeljugador(en4,4)nosemueve.
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
                        {
                            sprintf(msg_string,"Atacas al animal! Le haces %d HP de daño!          ",dmg);
                            draw_msg(msg_string,msg_buffer);
                        }
                        else
                            draw_msg("El animal esquiva tu intento de atacarlo.",msg_buffer);
                        wrefresh(msgs);
                    }                  //Si no, comer:
                    else if(matrix[4][3].entidad->tipo == 'x') //Alimentarse de un cadaver.
                    {
                        int heal = (rand()%20);
                        player->hitHP(player,-heal);
                        if(!matrix[4][3].entidad->eat(matrix[4][3].entidad,-1))
							matrix[4][3].entidad = NULL; //Eliminar cadaver cuando ya fue comido
                        wattron(msgs,COLOR_PAIR(1));
                        sprintf(msg_string,"Te alimentas del cadaver. Recuperas %d HP!          ",heal);
                        draw_msg(msg_string,msg_buffer);
                        wattroff(msgs,COLOR_PAIR(1));
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
                    sprintf(msg_string,"Te alimentas de la %s. Recuperas %d HP!          ",matrix[4][3].entidad->pPlanta->nombre,heal);
                    draw_msg(msg_string,msg_buffer);
                    wattroff(msgs,COLOR_PAIR(1));
                    matrix[4][3].entidad = NULL;
                    player->eat(player,1);
                }
                return 0;
            }
            
        }
        case 'u':
        {
            if(!matrix[3][4].entidad) //Si no hay entidad, mover.
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
                        {
                            sprintf(msg_string,"Atacas al animal! Le haces %d HP de daño!          ",dmg);
                            draw_msg(msg_string,msg_buffer);
                        }
                        else
                            draw_msg("El animal esquiva tu intento de atacarlo.",msg_buffer);
                    }                  //Si no, comer:
                    else if(matrix[3][4].entidad->tipo == 'x') //Alimentarse de un cadaver.
                    {
                        int heal = (rand()%20);
                        player->hitHP(player,-heal);
                        if(!matrix[3][4].entidad->eat(matrix[3][4].entidad,-1))
							matrix[3][4].entidad = NULL; //Eliminar cadaver cuando ya fue comido
                        wattron(msgs,COLOR_PAIR(1));
                        sprintf(msg_string,"Te alimentas del cadaver. Recuperas %d HP!          ",heal);
                        draw_msg(msg_string,msg_buffer);
                        wattroff(msgs,COLOR_PAIR(1));
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
                    sprintf(msg_string,"Te alimentas de la %s. Recuperas %d HP!          ",matrix[3][4].entidad->pPlanta->nombre,heal);
                    draw_msg(msg_string,msg_buffer);
                    wattroff(msgs,COLOR_PAIR(1));
                    matrix[3][4].entidad = NULL;
                    player->eat(player,1);
                }
                return 0;
            }
        }
        case 'd':
        {
            if(!matrix[5][4].entidad) //Si no hay entidad, mover.
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
                        {
                            sprintf(msg_string,"Atacas al animal! Le haces %d HP de daño!          ",dmg);
                            draw_msg(msg_string,msg_buffer);
                        }
                        else
                            draw_msg("El animal esquiva tu intento de atacarlo.",msg_buffer);
                    }                  //Si no, comer:
                    else if(matrix[5][4].entidad->tipo == 'x') //Alimentarse de un cadaver.
                    {
                        int heal = (rand()%20);
                        player->hitHP(player,-heal);
                        if(!matrix[5][4].entidad->eat(matrix[5][4].entidad,-1))
							matrix[5][4].entidad = NULL; //Eliminar cadaver cuando ya fue comido
                        wattron(msgs,COLOR_PAIR(1));
                        sprintf(msg_string,"Te alimentas del cadaver. Recuperas %d HP!          ",heal);
                        draw_msg(msg_string,msg_buffer);
                        wattroff(msgs,COLOR_PAIR(1));
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
                    sprintf(msg_string,"Te alimentas de la %s. Recuperas %d HP!          ",matrix[5][4].entidad->pPlanta->nombre,heal);
                    draw_msg(msg_string,msg_buffer);
                    wattroff(msgs,COLOR_PAIR(1));
                    matrix[5][4].entidad = NULL;
                    player->eat(player,1);
                }
                return 0;
            }
        }
    }
    return 0;
}
