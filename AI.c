#include "Cell.h"

extern WINDOW *msgs;

int carnivoreAI(struct Cell matrix[9][9], int i, int j,struct Animal *player)
{
    if( (    (i == 4) &&  (  (j == 5) || (j == 3)  )  ) || (  (j == 4) && ( (i == 3) || (i == 5)  )  )  )
    {
        int dmg = (rand() % 6) * matrix[i][j].entidad->pAnimalC->ataque;
        player->hitHP(player,dmg);
        char name[20];
        matrix[i][j].entidad->getName(matrix[i][j].entidad,name);
        if(dmg>0)
            mvwprintw(msgs,2, 1,"El %s te ataca, hace %d HP de daño!          ",name,dmg);
        else
            mvwprintw(msgs,2, 1,"El %s intenta atacarte, pero logras evadirlo.",name);
        mvwprintw(msgs,3, 1,"                       ");
        if(dmg > 20)
            mvwprintw(msgs,3, 1,"Es un golpe critico!");
        wrefresh(msgs);
        return dmg;
    }
    if( (i < 3) && (j < 3) )
    {   if(matrix[i+1][j+1].entidad == NULL)
        {
            matrix[i+1][j+1].entidad = matrix[i][j].entidad;
            matrix[i][j].entidad = NULL;
            return 0;
        }
    }
    if( (i > 5) && (j > 5) )
    {   
        if(matrix[i-1][j-1].entidad == NULL)
        {
            matrix[i-1][j-1].entidad = matrix[i][j].entidad;
            matrix[i][j].entidad = NULL;
            return 0;
        }
    }
    if( (i > 5) && (j < 3) )
    {
        if(matrix[i-1][j+1].entidad == NULL)
        {
            matrix[i-1][j+1].entidad = matrix[i][j].entidad;
            matrix[i][j].entidad = NULL;
            return 0;
        }
    }
    if( (i < 3) && (j > 5) )
    {
        if(matrix[i+1][j-1].entidad == NULL)
        {
            matrix[i+1][j-1].entidad = matrix[i][j].entidad;
            matrix[i][j].entidad = NULL;
            return 0;
        }
    }
    if(i>4)
    {
        if(matrix[i-1][j].entidad == NULL)
        {
            matrix[i-1][j].entidad = matrix[i][j].entidad;
            matrix[i][j].entidad = NULL;
            return 0;
        }
    }
    if(i<4)
    {
        if(matrix[i+1][j].entidad == NULL)
        {
            matrix[i+1][j].entidad = matrix[i][j].entidad;
            matrix[i][j].entidad = NULL;
            return 0;
        }
    }
    if(j>4)
    {
        if(matrix[i][j-1].entidad == NULL)
        {
            matrix[i][j-1].entidad = matrix[i][j].entidad;
            matrix[i][j].entidad = NULL;
            return 0;
        }
    }
    if(j<4)
    {
        if(matrix[i][j+1].entidad == NULL)
        {
            matrix[i][j+1].entidad = matrix[i][j].entidad;
            matrix[i][j].entidad = NULL;
            return 0;
        }
    }
    
    
    return 0;
}

int herbivoreAI(struct Cell matrix[9][9], int i, int j,struct Animal *player)
{
    int salto = matrix[i][j].entidad->pAnimalH->rand_mov;
    if( (i == 4) &&  (  (j == 5) || (j == 3)  ) )
    {
        if((rand() % 3) == 0)
        {
            if(matrix[(i+salto)%8][j].entidad == NULL)
            {
                    matrix[i+salto][j].entidad = matrix[i][j].entidad;
                    matrix[i][j].entidad = NULL;
                    return 0;
            }
        }
        else
        {
            if(matrix[i-1][j].entidad == NULL)
            {
                    matrix[i-1][j].entidad = matrix[i][j].entidad;
                    matrix[i][j].entidad = NULL;
                    return 0;
            }
        }
    }
    if(  (j == 4) && ( (i == 3) || (i == 5)  )  )
    {
        if((rand() % 3) == 0)
        {
            if(matrix[i][(j-salto)%8].entidad == NULL)
            {
                    matrix[i][(j-salto)%8].entidad = matrix[i][j].entidad;
                    matrix[i][j].entidad = NULL;
                    return 0;
            }
        }
        else
        {
            if(matrix[i][j+1].entidad == NULL)
            {
                    matrix[i][j+1].entidad = matrix[i][j].entidad;
                    matrix[i][j].entidad = NULL;
                    return 0;
            }
        }
    }
    return 0;
}
