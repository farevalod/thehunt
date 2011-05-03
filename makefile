all:
	gcc -Wall -l ncurses main.c -o main || cat README
