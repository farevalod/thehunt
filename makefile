all:
	@gcc -Wall main.c -o hunt -l ncurses || (echo 'ERROR: Debe instalar ncurses antes de compilar!' && cat README)
