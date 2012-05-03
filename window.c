#include <ncurses.h>
#include <stdlib.h>
#include "Cell.c"

int HEIGHT = 27;
int WIDTH = 55;


void chooseAnimalMenu(WINDOW *win, struct Animal **player)
{
    //Menu para seleccionar animal.    
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
    char ch;
    while(((ch = getch()) < '1') || ch > '9');
    int num = ch - '0'; //Se ve como un hack, pero el standard lo garantiza!
    if(num <= i)
    {
        crearCarnivoro(player,num);
    }
    else
    {
        num = num - i;
        crearHerbivoro(player,num);
    }
    char name[20];
    (*player)->getName(*player,name);
    mvwprintw(win,20,10,"Animal seleccionado: %s",name);
    wrefresh(win);
    getch();
    free(paC);
    free(paH);
    return;
}

void draw_grass(WINDOW *local_win, int x, int y)
{
    //Dibujar el pasto sobre el mapa.
	wattron(local_win,COLOR_PAIR(1));
    mvwprintw(local_win,x, y,"%c",(44 + 2*(rand()%2)));
    wrefresh(local_win);
	wattroff(local_win,COLOR_PAIR(1));
	return;
}

void draw_welcome(WINDOW *main_win, WINDOW *msg_win, struct Animal **player)
{
    //Mensajes de bienvenida.
    wattron(msg_win,COLOR_PAIR(2));
    draw_msg("THE HUNT FOR LIFE",msg_buffer);
    wattroff(msg_win,COLOR_PAIR(2));
    draw_msg("Iniciando simulacion de ecosistema...",msg_buffer);
    chooseAnimalMenu(main_win,player);
    return;
}

void draw_matrix(WINDOW *local_win, struct Cell matrix[9][9], struct Animal *player)
{
    //Recorrer y dibujar la matrix.
    int i, j;           //Contadores de loop
    int x, y;           //Coordenadas en pantalla.
    char ch;
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            x = matrix[i][j].xpos;
            y = matrix[i][j].ypos;
            if((i == 4) && (j == 4))
            {
                char name[20];
                player->getName(player,name);
                switch(player->tipo)
                {
                    case 'c':
                        wattron(local_win,COLOR_PAIR(2));
                        mvwprintw(local_win,x,y,"%c",name[0]);
                        wattroff(local_win,COLOR_PAIR(2));
                        continue;
                    case 'h':
                        wattron(local_win,COLOR_PAIR(1));
                        mvwprintw(local_win,x,y,"%c",name[0]);
                        wattroff(local_win,COLOR_PAIR(1));
                        continue;
                }
            }
            if(matrix[i][j].entidad != NULL)
            {
                ch = (matrix[i][j].entidad)->tipo;
                switch(ch)
                {
                    case('c'):
                        wattron(local_win,COLOR_PAIR(2));
                        mvwprintw(local_win,x,y,"%c",ch);
                        wattroff(local_win,COLOR_PAIR(2));
                        break;
                    case('h'):
                        wattron(local_win,COLOR_PAIR(4));
                        mvwprintw(local_win,x,y,"%c",ch);
                        wattroff(local_win,COLOR_PAIR(4));
                        break;
                    case('p'):
                        wattron(local_win,COLOR_PAIR(1));
                        mvwprintw(local_win,x,y,"%c",ch);
                        wattroff(local_win,COLOR_PAIR(1));
                        break;
                    case 'x':
                        wattron(local_win,COLOR_PAIR(3));
                        mvwprintw(local_win,x,y,"x");
                        wattroff(local_win,COLOR_PAIR(3));
                        continue;
                }
            }
            else
                draw_grass(local_win,x,y);
        }
    }
}

void draw_stats(WINDOW *stat_window, struct Animal *player, int lim)
{
    mvwprintw(stat_window,1,1,"HP: %d  ",player->getHP(player));
    mvwprintw(stat_window,2,1,"Comidas: %d / %d",player->eat(player,0),lim);
    wrefresh(stat_window);
    return;
}

void draw_msg(char *msg, char buffer[5][55])
{
    strcpy(buffer[0],buffer[1]);
    strcpy(buffer[1],buffer[2]);
    strcpy(buffer[2],buffer[3]);
    strcpy(buffer[3],buffer[4]);
    strcpy(buffer[4],msg);
    int i;
    for(i=0;i<5;i++)
    {
        if(buffer[i][0] == 'T')
            wattron(msgs,COLOR_PAIR(1));
        if(buffer[i][0] == 'E')
            wattron(msgs,COLOR_PAIR(2));
        if(buffer[i][0] == 'A')
            wattron(msgs,COLOR_PAIR(4));
        mvwprintw(msgs,2+i, 1,"%s                     ",buffer[i]);
        if(buffer[i][0] == 'T')
            wattroff(msgs,COLOR_PAIR(1));
        if(buffer[i][0] == 'E')
            wattroff(msgs,COLOR_PAIR(2));
        if(buffer[i][0] == 'A')
            wattroff(msgs,COLOR_PAIR(4));
    }
    wrefresh(msgs);
    return;
}

WINDOW *create_newwin(int HEIGHT, int WIDTH, int starty, int startx)
{
    WINDOW *local_win;
	local_win = newwin(HEIGHT, WIDTH, starty, startx);
	box(local_win, 0 , 0);
	wrefresh(local_win);
	return local_win;
}
