#include "Cell.h"

int carnivoreAI(struct Cell matrix[9][9], int i, int j,struct Animal *player)
{
    if( (    (i == 4) &&  (  (j == 5) || (j == 3)  )  ) || (  (j == 4) && ( (i == 3) || (i == 5)  )  )  )
    {
        int dmg = (rand() % 6) * matrix[i][j].entidad->pAnimalC->ataque;
        player->hitHP(player,dmg);
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
    if(i>5)
    {
        if(matrix[i-1][j].entidad == NULL)
        {
            matrix[i-1][j].entidad = matrix[i][j].entidad;
            matrix[i][j].entidad = NULL;
            return 0;
        }
    }
    if(i<3)
    {
        if(matrix[i+1][j].entidad == NULL)
        {
            matrix[i+1][j].entidad = matrix[i][j].entidad;
            matrix[i][j].entidad = NULL;
            return 0;
        }
    }
    if(j>5)
    {
        if(matrix[i][j-1].entidad == NULL)
        {
            matrix[i][j-1].entidad = matrix[i][j].entidad;
            matrix[i][j].entidad = NULL;
            return 0;
        }
    }
    if(j<3)
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
    return 0;
}
