all: clean
	gcc -o ncursesPallet ncursesPallet.c -lncurses -Wall -std=c11

clean:
	-rm ncursesPallet
