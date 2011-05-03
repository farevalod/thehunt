#include <ncurses.h>
#include <stdlib.h>
#include "Cell.c"

int HEIGHT = 27;
int WIDTH = 55;


void chooseAnimalMenu(WINDOW *win, struct Animal **player)
{
    int i = 0,j = 0, nCarnivoros, nHerbivoros;
    FILE *fp = fopen("carnivores.txt","r");
    fscanf(fp,"%d",&nCarnivoros);
    fclose(fp);
    fp = fopen("herbivores.txt","r");
    fscanf(fp,"%d",&nHerbivoros);
    fclose(fp);
    struct AnimalCarnivoro *paC = (struct AnimalCarnivoro *)malloc(sizeof(struct AnimalCarnivoro));
    struct AnimalHerbivoro *paH = (struct AnimalHerbivoro *)malloc(sizeof(struct AnimalHerbivoro));
    wattron(win,COLOR_PAIR(2));
    mvwprintw(win,4,8,"%s","Carnivoros");
    wattroff(win,COLOR_PAIR(2));
    wattron(win,COLOR_PAIR(1));
    mvwprintw(win,4,28,"%s","Herbivoros");
    wattroff(win,COLOR_PAIR(1));
    for(i=0;i<nCarnivoros;i++)
    {
        getDatosCarnivoro(paC->nombre,&(paC->vida),&(paC->ataque),i);
        mvwprintw(win,i+5,10,"%d. %s",i+1,paC->nombre);
    }
    for(j=0;j<nHerbivoros;j++)
    {
        getDatosHerbivoro(paH->nombre,&(paH->vida),&(paH->defensa),&(paH->rand_mov),j);
        mvwprintw(win,j+5,30,"%d. %s",j+i+1,paH->nombre);
    }
    mvwprintw(win,15,10,"%s","Seleccione el animal a utilizar: ");
    wrefresh(win);
    char ch = getch();
    int num = ch - '0'; //Se ve como un hack, pero el standard lo garantiza!
    if(num < i)
    {
        getDatosCarnivoro((*player)->pAnimalC->nombre,&((*player)->pAnimalC->vida),&((*player)->pAnimalC->ataque),num);
    }
    else
    {
        num = num - i;
        getDatosHerbivoro((*player)->pAnimalH->nombre,&((*player)->pAnimalH->vida),&((*player)->pAnimalH->defensa),&((*player)->pAnimalH->rand_mov),num);
    }
    mvwprintw(win,20,10,"%s","Animal seleccionado: ");
    wrefresh(win);
    free(paC);
    free(paH);
    return;
}

void draw_grass(WINDOW *local_win, int x, int y)
{
	wattron(local_win,COLOR_PAIR(1));
    mvwprintw(local_win,x, y,"%c",(44 + 2*(rand()%2)));
    wrefresh(local_win);
	wattroff(local_win,COLOR_PAIR(1));
	return;
}

void draw_welcome(WINDOW *main_win, WINDOW *msg_win, struct Animal **player)
{
    chooseAnimalMenu(main_win,player);
    wattron(msg_win,COLOR_PAIR(2));
    mvwprintw(msg_win,1, 1,"%s", "THE HUNT FOR LIFE");
    wattroff(msg_win,COLOR_PAIR(2));
    mvwprintw(msg_win,2, 1,"%s", "Iniciando simulacion de ecosistema...");
    wrefresh(msg_win);
}

void draw_matrix(WINDOW *local_win, struct Cell matrix[9][9])
{
    int i, j;
    int x, y;
    char ch;
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            x = matrix[i][j].xpos;
            y = matrix[i][j].ypos;
            if(matrix[i][j].entidad != NULL)
            {
                ch = (matrix[i][j].entidad)->tipo;
                mvwprintw(local_win,x, y,"%c",ch);
            }
            else
                draw_grass(local_win,x,y);
        }
    }
    
}

void draw_stats(WINDOW *stat_window, struct Animal player)
{
    if(player.tipo == 'c')
        mvwprintw(stat_window,1,1,"HP: %d",player.pAnimalC->vida);
    else
        mvwprintw(stat_window,1,1,"HP: %d",player.pAnimalH->vida);
    return;
}

WINDOW *create_newwin(int HEIGHT, int WIDTH, int starty, int startx)
{	
    WINDOW *local_win;

	local_win = newwin(HEIGHT, WIDTH, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}
