CC = gcc
CFLAGS = -g -Wall -std=c11 -D_XOPEN_SOURCE=700 -D_POSIX_C_SOURCE=200809L -D_POSIX_SOURCE=1 -D_DEFAULT_SOURCE=1 -D_GNU_SOURCE=1
#CFLAGS = -O2 -Wall -std=c11 -D_XOPEN_SOURCE=700 -D_POSIX_C_SOURCE=200809L -D_POSIX_SOURCE=1 -D_DEFAULT_SOURCE=1 -D_GNU_SOURCE=1

RM = rm -f

all: clean
	$(CC) -o ncursesPallet ncursesPallet.c -lncurses $(CFLAGS)

clean:
	-$(RM) ncursesPallet
