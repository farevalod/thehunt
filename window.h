#ifndef WIN_H
#define WIN_H

void chooseAnimalMenu(WINDOW *win, struct Animal **player);
void draw_grass(WINDOW *local_win, int x, int y);
void draw_welcome(WINDOW *main_win, WINDOW *msg_win, struct Animal **player);
void draw_matrix(WINDOW *local_win, struct Cell matrix[9][9], struct Animal *player);
void draw_stats(WINDOW *stat_window, struct Animal *player, int lim);
void draw_msg(char *msg, char buffer[5][55]);
WINDOW *create_newwin(int HEIGHT, int WIDTH, int starty, int startx);

#endif
