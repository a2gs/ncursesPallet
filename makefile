all: clean
	cc -o ncursesPallet ncursesPallet.c -lncurses -Wall

clean:
	-rm ncursesPallet
