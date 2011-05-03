all:
	@gcc -Wall -l ncurses main.c -o hunt || (echo 'ERROR: Debe instalar ncurses antes de compilar!' && cat README)
