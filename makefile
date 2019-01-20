all: clean
	gcc -o ncursesPallet ncursesPallet.c -lncurses -Wall

clean:
	-rm ncursesPallet
