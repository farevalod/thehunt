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
  	char msg_buffer[5][55]; //Buffer de mensajes.

int nonCanonical()
{
    /*
        Configura el tty para modo no-canónico.
        Ésto quiere decir, permítame manejar de forma
        directa todos los inputs de teclado, y hacer
        read() no-bloqueante.
        Importante, se debe restaurar el estado original
        del tty. De otra forma, puede causar problemas,
        aún después de finalizar la ejecución del programa.
    */
    struct termios termios_p;
    termios_p.c_cc[VMIN]  =  0;
    termios_p.c_cc[VTIME] =  3;
	termios_p.c_lflag &= ~( ECHO|ICANON|ISIG|ECHOE|ECHOK|ECHONL );
    termios_p.c_oflag &= ~( OPOST );
    return( tcsetattr( 0, TCSADRAIN, &termios_p ) );
}

int canonical(struct termios *saved)
{   //Restaura la configuración original del usuario.
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
	keypad(stdscr, TRUE);		/* Activa las teclas de control. */

	starty = (LINES - HEIGHT) / 4;	/* Calcula la posición del centro de la pantalla */
	startx = (COLS - WIDTH) / 2;
	printw("Presione Q para salir");
	refresh();
	my_win = create_newwin(HEIGHT, WIDTH, starty, startx);
	stats = create_newwin(6,30,starty, startx+60);
	msgs = create_newwin(9,80,starty+30,startx-13);
	struct Animal *player;
    player = (struct Animal *)malloc(sizeof(struct Animal));
	draw_welcome(my_win,msgs,&player);
	my_win = create_newwin(HEIGHT, WIDTH, starty, startx);
    struct Nodo *cList = NULL;      //  ]
    struct Nodo *hList = NULL;      //   -> Los animales leidos se guardan en éstas listas.
    struct Nodo *pList = NULL;      //  ]
    int lim = loadData(&cList,&hList,&pList); //Carga las listas de animales, y devuelve el número de comidas.
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
    while(!end)
	{
	    ch = '0';
	    read(0,&ch,1);      //Se lée el (posible) input del usuario.
	    if(!(i % 3))
    	    iterateMatrix(matrix,player);   //Los NPC reaccionan cada 3 ticks.
    	i++;
	    switch(ch)
		{	case 'a':
		        if(!apply(matrix,player,&cList,&hList,&pList,'l'))
	                draw_matrix(my_win,matrix,player);
               	wrefresh(my_win);
				break;
			case 'd':
			    if(!apply(matrix,player,&cList,&hList,&pList,'r'))
    	            draw_matrix(my_win,matrix,player);
	            wrefresh(my_win);
				break;
			case 'w':
			    if(!apply(matrix,player,&cList,&hList,&pList,'u'))
	                draw_matrix(my_win,matrix,player);
	            wrefresh(my_win);
   				break;
			case 's':
			    if(!apply(matrix,player,&cList,&hList,&pList,'d'))
	                draw_matrix(my_win,matrix,player);
	            wrefresh(my_win);
				break;
		    case 'q':
		        end = 1;
		        break;
		    default: draw_matrix(my_win,matrix,player);
		}
		if(player->eat(player,0) >= lim)
		{
		    draw_msg("Limite de comidas alcanzado! Felicitaciones!",msg_buffer);
            draw_msg("                                            ",msg_buffer);
            draw_msg("                                            ",msg_buffer);
		    canonical(&defs);
            getch();
		    end = 1;
		}
		if(player)
		    draw_stats(stats, player, lim);
		if(player->getHP(player) < 1)
		{
            wattron(my_win,COLOR_PAIR(3));
            for(i=-1;i<2;i++)
                for(j=-1;j<2;j++)
                    mvwprintw(my_win,px+i,py+j," ");
            mvwprintw(my_win,px,py,"X");
            wattroff(my_win,COLOR_PAIR(3));
            wrefresh(my_win);
            draw_msg("Has sido devorado...                      ",msg_buffer);
            draw_msg("                                          ",msg_buffer);
            draw_msg("                                          ",msg_buffer);
            end = 1;
            canonical(&defs);
            getch();
        }		    
	}
    canonical(&defs);
	endwin();			/* End curses mode		  */
    
    return 0;
}
