/******** Archivo: main.c ********
Descripcion: Loop principal del juego

Funciones:   
    
************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include "window.c"
#include "loadData.c"
#include "ncurses.h"

    WINDOW *my_win;
    WINDOW *stats;
    WINDOW *msgs;

int nonCanonical()
{
    struct termios termios_p;
    termios_p.c_cc[VMIN]  =  0;
    termios_p.c_cc[VTIME] =  3;
        termios_p.c_lflag &= ~( ECHO|ICANON|ISIG|
              ECHOE|ECHOK|ECHONL );
    termios_p.c_oflag &= ~( OPOST );
    
    return( tcsetattr( 0, TCSADRAIN, &termios_p ) );
}

int canonical(struct termios *saved)
{
    return( tcsetattr( 0, TCSADRAIN, saved ) );
}

int main()
{
    srand( time(NULL) );
    
    struct termios defs;    //Se guarda el estado actual de termios.
    tcgetattr(0,&defs);     //No queremos contaminar el tty del usuario
                            //(Asi es, el tty, no solo el proceso!)                          
	int startx, starty;

	initscr();			/* Start curses mode 		*/
	cbreak();			/* Line buffering disabled, Pass on */
					    /* everty thing to me 		*/
    start_color();
    use_default_colors();
    init_pair(1, COLOR_GREEN, -1);
    init_pair(2, COLOR_RED, -1);
    init_pair(3, COLOR_YELLOW, COLOR_RED);
    init_pair(4, COLOR_YELLOW,-1);
	keypad(stdscr, TRUE);		/* I need that nifty F1 	*/

	starty = (LINES - HEIGHT) / 4;	/* Calculating for a center placement */
	startx = (COLS - WIDTH) / 2;	/* of the window		*/
	printw("Presione Q para salir");
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
    int px = matrix[4][4].xpos;
    int py = matrix[4][4].ypos;
    
    //GAME LOOP:
    //Primero, setear modo no-canonico
    //Esto permite obtener input en tiempo real
    //y no bloquar la ejecución mientras el usuario juega.

    nonCanonical();
    char ch; int end; int i = 0; int j = 0;
    while(end != 1)
	{
	    ch = '0';
	    read(0,&ch,1);
	    if((i % 3) == 0)
    	    iterateMatrix(matrix,player);
    	i++;
	    switch(ch)
		{	case 'a':
		        if(apply(matrix,player,&cList,&hList,&pList,'l') == 0)
	                draw_matrix(my_win,matrix,player);
               	wrefresh(my_win);
				break;
			case 'd':
			    if(apply(matrix,player,&cList,&hList,&pList,'r') == 0)
    	            draw_matrix(my_win,matrix,player);
	            wrefresh(my_win);
				break;
			case 'w':
			    if(apply(matrix,player,&cList,&hList,&pList,'u') == 0)
	                draw_matrix(my_win,matrix,player);
	            wrefresh(my_win);
   				break;
			case 's':
			    if(apply(matrix,player,&cList,&hList,&pList,'d') == 0)
	                draw_matrix(my_win,matrix,player);
	            wrefresh(my_win);
				break;
		    case 'q':
		        end = 1;
		        break;
		    default: draw_matrix(my_win,matrix,player);
		}
		if(player->eat(player,0) > 10)
		{
		    mvwprintw(msgs,2, 1,"%s", "Limite de comidas alcanzado! Felicitaciones!           ");
            mvwprintw(msgs,3, 1,"%s", "                                                       ");
            wrefresh(msgs);            
		    canonical(&defs);
            getch();
		    end = 1;
		}
		if(player != NULL)
		    draw_stats(stats, player);
		if(player->getHP(player) < 1)
		{
            wattron(my_win,COLOR_PAIR(3));
            for(i=-1;i<2;i++)
                for(j=-1;j<2;j++)
                    mvwprintw(my_win,px+i,py+j," ");
            mvwprintw(my_win,px,py,"X");
            wattroff(my_win,COLOR_PAIR(3));
            wrefresh(my_win);
            mvwprintw(msgs,2, 1,"%s", "Has sido devorado...                                   ");
            mvwprintw(msgs,3, 1,"%s", "                                                       ");
            wrefresh(msgs);
            end = 1;
            canonical(&defs);
            getch();
        }		    
	}
    canonical(&defs);
	endwin();			/* End curses mode		  */
    
    return 0;
}
