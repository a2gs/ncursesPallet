CC = gcc
CFLAGS = -g -Wall -std=c11 -D_XOPEN_SOURCE=700
RM = rm -f

all: clean
	$(CC) -o ncursesPallet ncursesPallet.c -lncurses $(CFLAGS)

clean:
	-$(RM) ncursesPallet
