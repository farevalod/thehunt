#include <ncurses.h>
#include <stdlib.h>
#include "Cell.c"

int HEIGHT = 24;
int WIDTH = 48;

void draw_grass(WINDOW *local_win, int x, int y)
{
	wattron(local_win,COLOR_PAIR(1));
    mvwprintw(local_win,x, y,"%c",(44 + 2*(rand()%2)));
    wrefresh(local_win);
	wattroff(local_win,COLOR_PAIR(1));
	return;
}

void draw_matrix(WINDOW *local_win, struct Cell matrix[8][8])
{
    int i, j;
    int x, y;
    char ch;
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
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
