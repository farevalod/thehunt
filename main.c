/******** Archivo: main.c ********
Descripcion: Loop principal del juego

Funciones:   
    
************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "window.c"
#include "loadData.c"
#include "ncurses.h"

int main()
{
    srand( time(NULL) );
    
    WINDOW *my_win;
	int startx, starty;
	int ch;

	initscr();			/* Start curses mode 		*/
	cbreak();			/* Line buffering disabled, Pass on
					 * everty thing to me 		*/
    start_color();
    use_default_colors();
    init_pair(1, COLOR_GREEN, -1);
	keypad(stdscr, TRUE);		/* I need that nifty F1 	*/

	starty = (LINES - HEIGHT) / 4;	/* Calculating for a center placement */
	startx = (COLS - WIDTH) / 2;	/* of the window		*/
	printw("Press F1 to exit");
	refresh();
	my_win = create_newwin(HEIGHT, WIDTH, starty, startx);
	
    struct Nodo *cList = NULL;
    struct Nodo *hList = NULL;
    struct Nodo *pList = NULL;
    loadData(&cList,&hList,&pList);
    struct Cell matrix[8][8];
    initMatrix(matrix);
    
    //GAME LOOP
    while((ch = getch()) != KEY_F(1))
	{	
	    switch(ch)
		{	case KEY_LEFT:
		        apply(matrix,&cList,&hList,&pList,'l');
	            draw_matrix(my_win,matrix);
               	wrefresh(my_win);
				break;
			case KEY_RIGHT:
			    apply(matrix,&cList,&hList,&pList,'r');
	            draw_matrix(my_win,matrix);
	            wrefresh(my_win);
				break;
			case KEY_UP:
			    apply(matrix,&cList,&hList,&pList,'u');
	            draw_matrix(my_win,matrix);
	            wrefresh(my_win);
   				break;
			case KEY_DOWN:
			    apply(matrix,&cList,&hList,&pList,'d');
	            draw_matrix(my_win,matrix);
				break;
		}
	}
		
	endwin();			/* End curses mode		  */
    
    return 0;
}
