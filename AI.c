#include "Cell.h"
#include "window.h"

extern WINDOW *msgs;
extern char msg_buffer[5][55];

int carnivoreAI(struct Cell matrix[9][9], int i, int j,struct Animal *player)
{

    //Posiciones adjacentes al jugador.
    if(((i==4)&&((j==5)||(j==3)))||((j==4)&&((i==3)||(i==5))))
    {
        int dmg = (rand() % 7) * matrix[i][j].entidad->pAnimalC->ataque;
        player->hitHP(player,dmg);
        char name[20];
        matrix[i][j].entidad->getName(matrix[i][j].entidad,name);
        char msg_string[55];
        sprintf(msg_string,"El %s te ataca, hace %d HP de daño!          ",name,dmg);
        if(dmg>0)
            draw_msg(msg_string,msg_buffer);
        else
        {
            sprintf(msg_string,"El %s intenta atacarte, pero logras evadirlo.",name);
            draw_msg(msg_string,msg_buffer);
        }
        if(dmg > 20)
            draw_msg("Es un golpe critico!",msg_buffer);
        wrefresh(msgs);
        return dmg;
    }
	if((i<3)&&(j<3)&&(!(matrix[i+1][j+1].entidad)))
    {   
		matrix[i+1][j+1].entidad = matrix[i][j].entidad;
		matrix[i][j].entidad = NULL;
		return 0;
    }
	if((i>5)&&(j>5)&&(!(matrix[i-1][j-1].entidad)))
    {   
		matrix[i-1][j-1].entidad = matrix[i][j].entidad;
		matrix[i][j].entidad = NULL;
		return 0;
    }
	if((i>5)&&(j<3)&&(!(matrix[i-1][j+1].entidad)))
    {
		matrix[i-1][j+1].entidad = matrix[i][j].entidad;
		matrix[i][j].entidad = NULL;
		return 0;
    }
	if((i<3)&&(j>5)&&(!(matrix[i+1][j-1].entidad)))
    {
		matrix[i+1][j-1].entidad = matrix[i][j].entidad;
		matrix[i][j].entidad = NULL;
		return 0;
    }
    if(i>4&&(!(matrix[i-1][j].entidad)))
    {
		matrix[i-1][j].entidad = matrix[i][j].entidad;
		matrix[i][j].entidad = NULL;
		return 0;
    }
    if(i<4&&(!(matrix[i+1][j].entidad)))
    {
		matrix[i+1][j].entidad = matrix[i][j].entidad;
		matrix[i][j].entidad = NULL;
		return 0;
    }
    if(j>4 && (!(matrix[i][j-1].entidad)))
    {
		matrix[i][j-1].entidad = matrix[i][j].entidad;
		matrix[i][j].entidad = NULL;
		return 0;
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
	if((i==4)&&((j==5)||(j==3)))
    {
        if((rand() % 3) == 0)
        {
            if(!(matrix[(i+salto)%8][j].entidad))
            {
                    matrix[i+salto][j].entidad = matrix[i][j].entidad;
                    matrix[i][j].entidad = NULL;
                    return 0;
            }
        }
        else
        {
            if(!(matrix[i-1][j].entidad))
            {
                    matrix[i-1][j].entidad = matrix[i][j].entidad;
                    matrix[i][j].entidad = NULL;
                    return 0;
            }
        }
    }
    if(  (j == 4) && ( (i == 3) || (i == 5)  )  )
    {
        if(!(rand() % 3))
        {
            if(!(matrix[i][(j-salto)%8].entidad))
            {
                    matrix[i][(j-salto)%8].entidad = matrix[i][j].entidad;
                    matrix[i][j].entidad = NULL;
                    return 0;
            }
        }
        else
        {
            if(!(matrix[i][j+1].entidad))
            {
                    matrix[i][j+1].entidad = matrix[i][j].entidad;
                    matrix[i][j].entidad = NULL;
                    return 0;
            }
        }
    }
    return 0;
}
