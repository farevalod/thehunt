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
    WINDOW *stats;
    WINDOW *msgs;
	int startx, starty;
	int ch;

	initscr();			/* Start curses mode 		*/
	cbreak();			/* Line buffering disabled, Pass on */
					    /* everty thing to me 		*/
    start_color();
    use_default_colors();
    init_pair(1, COLOR_GREEN, -1);
    init_pair(2, COLOR_RED, -1);
	keypad(stdscr, TRUE);		/* I need that nifty F1 	*/

	starty = (LINES - HEIGHT) / 4;	/* Calculating for a center placement */
	startx = (COLS - WIDTH) / 2;	/* of the window		*/
	printw("Presione F1 para salir");
	refresh();
	my_win = create_newwin(HEIGHT, WIDTH, starty, startx);
	stats = create_newwin(6,30,starty, startx+60);
	msgs = create_newwin(6,80,starty+30,startx-13);
	struct Animal *player;
    player = (struct Animal *)malloc(sizeof(struct Animal));
	draw_welcome(my_win,msgs,&player);
	my_win = create_newwin(HEIGHT, WIDTH, starty, startx);
    struct Nodo *cList = NULL;      //  ]
    struct Nodo *hList = NULL;      //   -> Los animales leidos se guardan en éstas listas.
    struct Nodo *pList = NULL;      //  ]
    loadData(&cList,&hList,&pList);
    struct Cell matrix[9][9];
    initMatrix(matrix);
    
    //GAME LOOP
    while((ch = getch()) != KEY_F(1))
	{	
	    switch(ch)
		{	case KEY_LEFT:
		        if(apply(matrix,&cList,&hList,&pList,'l') == 0)
	                draw_matrix(my_win,matrix,player);
               	wrefresh(my_win);
				break;
			case KEY_RIGHT:
			    if(apply(matrix,&cList,&hList,&pList,'r') == 0)
    	            draw_matrix(my_win,matrix,player);
	            wrefresh(my_win);
				break;
			case KEY_UP:
			    if(apply(matrix,&cList,&hList,&pList,'u') == 0)
	                draw_matrix(my_win,matrix,player);
	            wrefresh(my_win);
   				break;
			case KEY_DOWN:
			    if(apply(matrix,&cList,&hList,&pList,'d') == 0)
	                draw_matrix(my_win,matrix,player);
	            wrefresh(my_win);
				break;
		}
		if(player != NULL)
		    draw_stats(stats, player);
	}
		
	endwin();			/* End curses mode		  */
    
    return 0;
}
