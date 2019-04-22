/* Andre Augusto Giannotti Scota (a2gs)
 * andre.scota@gmail.com
 *
 * A sample of NCurses colors and attributes.
 *
 * MIT License
 *
 */

/* ncursesPallet.c
 * A sample of NCurses colors and attributes.
 *
 *  Who     | When       | What
 *  --------+------------+----------------------------
 *   a2gs   | 19/01/2019 | Creation
 *          |            |
 */


/* *** INCLUDES ************************************************************************ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>


/* *** DEFINES AND LOCAL DATA TYPE DEFINATION ****************************************** */
#define MIN_COLS		(80)
#define DEFAULT_SCREEN		(1)
#define USER_SCREEN		(2)


/* *** LOCAL PROTOTYPES (if applicable) ************************************************ */


/* *** EXTERNS / LOCAL / GLOBALS VARIEBLES ********************************************* */


/* *** FUNCTIONS *********************************************************************** */
int save_colors_attr_curs(WINDOW *win, int *savedFG, int *savedBG, unsigned long *savedAT)
{
	chtype ch = 0;
	int bgcolor = 0, att = 0 /*, chtext = 0*/;
	short sSavedFG = 0, sSavedBG = 0;

	ch = getbkgd(win);

	bgcolor = (ch & A_COLOR) >> 8;
	att = (ch & A_ATTRIBUTES);
	/*chtext = (ch & A_CHARTEXT);*/

	pair_content(bgcolor, &sSavedFG, &sSavedBG);

	*savedFG = sSavedFG;
	*savedBG = sSavedBG;
	*savedAT = att;

	return(0);
}

int main(int argc, char *argv[])
{
	char text[MIN_COLS + 1] = {'\0'};
	int cursor = 0;
	int nc= 0, keyPressed = 0;
	int nlFG = 0, nlBG = 0, nlAT1 = 0, nlAT2 = 0, nlAT3 = 0;
	int savedFG = 0, savedBG = 0;
	unsigned long savedAT = 0;
	unsigned int  colors_BGFG[]={COLOR_BLACK, COLOR_RED, COLOR_GREEN, COLOR_YELLOW, COLOR_BLUE, COLOR_MAGENTA, COLOR_CYAN, COLOR_WHITE};
	unsigned long attributes []={A_NORMAL, A_STANDOUT, A_UNDERLINE, A_REVERSE, A_BLINK, A_DIM, A_BOLD, A_PROTECT, A_INVIS, A_ALTCHARSET, A_ITALIC, A_CHARTEXT, A_COLOR};

	initscr();
	keypad(stdscr, TRUE);
	cbreak();
	noecho();

	if(LINES < 24 || COLS < 80){
		endwin();
		printf("Seu terminal nao tem a dimensao minima de 24 linhas por 80 colunas (sua resolucao eh %dlx%dc).\n", LINES, COLS);
		return(-1);
	}

	if(has_colors() == FALSE){
		endwin();
		printf("Terminal nao suporta cores (has_colors() = FALSE).\n");
		return(-1);
	}

	if(can_change_color() == FALSE){
		endwin();
		printf("Terminal nao suporta mudar as cores (can_change_colors() = FALSE).\n");
		return(-1);
	}

	if(start_color() != OK){
		endwin();
		printf("Erro em iniciar cores (start_colors() = FALSE).\n");
		return(-1);
	}

	cursor = curs_set(0);
	save_colors_attr_curs(stdscr, &savedFG, &savedBG, &savedAT);

	/* Saving default colors */
	init_pair(DEFAULT_SCREEN, savedFG, savedBG);

	do{
		clear();

		/* Default screen */
		attron(COLOR_PAIR(DEFAULT_SCREEN));
		attron(savedAT);

		refresh();

		snprintf(text, MIN_COLS, "Dimensao do terminal: Cols[%d] Lines[%d].", COLS, LINES);
		mvaddstr(0, (int)((COLS/2)-(strlen(text)/2)), text);

		mvaddstr(2, 0, "Use os direcionais ou [END] para sair.");

		          /* nc       0         1           2           3      */
		mvaddstr( 5, 0, "+---------+---------+------------+------------+------------+");
		mvaddstr( 6, 0, "|    FG   |   BG    |    ATTR1   |   ATTR2    |   ATTR3    |");
		mvaddstr( 7, 0, "+---------+---------+------------+------------+------------+"); /* nl */
		mvaddstr( 8, 0, "| BLACK   | BLACK   | NORMAL     | NORMAL     | NORMAL     |"); /* 0 */
		mvaddstr( 9, 0, "| RED     | RED     | STANDOUT   | STANDOUT   | STANDOUT   |"); /* 1 */
		mvaddstr(10, 0, "| GREEN   | GREEN   | UNDERLINE  | UNDERLINE  | UNDERLINE  |"); /* 2 */
		mvaddstr(11, 0, "| YELLOW  | YELLOW  | REVERSE    | REVERSE    | REVERSE    |"); /* 3 */
		mvaddstr(12, 0, "| BLUE    | BLUE    | BLINK      | BLINK      | BLINK      |"); /* 4 */
		mvaddstr(13, 0, "| MAGENTA | MAGENTA | DIM        | DIM        | DIM        |"); /* 5 */
		mvaddstr(14, 0, "| CYAN    | CYAN    | BOLD       | BOLD       | BOLD       |"); /* 6 */
		mvaddstr(15, 0, "| WHITE   | WHITE   | PROTECT    | PROTECT    | PROTECT    |"); /* 7 */
		mvaddstr(16, 0, "|         |         | INVIS      | INVIS      | INVIS      |"); /* 8 */
		mvaddstr(17, 0, "|         |         | ALTCHARSET | ALTCHARSET | ALTCHARSET |"); /* 9 */
		mvaddstr(18, 0, "|         |         | ITALIC     | ITALIC     | ITALIC     |"); /* 10 */
		mvaddstr(19, 0, "|         |         | CHARTEXT   | CHARTEXT   | CHARTEXT   |"); /* 11 */
		mvaddstr(20, 0, "|         |         | COLOR      | COLOR      | COLOR      |"); /* 12 */
		mvaddstr(21, 0, "+---------+---------+------------+------------+------------+");

		if     (nc == 0) mvaddstr(4, 5 , "V");
		else if(nc == 1) mvaddstr(4, 15, "V");
		else if(nc == 2) mvaddstr(4, 27, "V");
		else if(nc == 3) mvaddstr(4, 40, "V");
		else             mvaddstr(4, 52, "V");

		mvaddstr(nlFG +8,  1, ">");
		mvaddstr(nlBG +8, 11, ">");
		mvaddstr(nlAT1+8, 21, ">");
		mvaddstr(nlAT2+8, 34, ">");
		mvaddstr(nlAT3+8, 47, ">");

		refresh();
		attroff(COLOR_PAIR(DEFAULT_SCREEN));
		attroff(savedAT);

		/* Setting the sample sring out */
		init_pair(USER_SCREEN, colors_BGFG[nlFG], colors_BGFG[nlBG]);
		attron(COLOR_PAIR(USER_SCREEN));
		attron(attributes[nlAT1] | attributes[nlAT2] | attributes[nlAT3]);

		snprintf(text, MIN_COLS, "\"Now I will have less distraction.\" -Euler");
		mvaddstr(13, (int)((COLS/2)-(strlen(text)/2)), text);

		attroff(COLOR_PAIR(USER_SCREEN));
		attroff(attributes[nlAT1] | attributes[nlAT2] | attributes[nlAT3]);
		refresh();

		/* Menu control */
		switch(keyPressed = getch()){
			case KEY_DOWN:
				if     (nc == 0) (nlFG == 7)   ? nlFG = 0  : nlFG++; /* FG */
				else if(nc == 1) (nlBG == 7)   ? nlBG = 0  : nlBG++; /* BG */
				else if(nc == 2) (nlAT1 == 12) ? nlAT1 = 0 : nlAT1++; /* attributes1 */
				else if(nc == 3) (nlAT2 == 12) ? nlAT2 = 0 : nlAT2++; /* attributes2 */
				else             (nlAT3 == 12) ? nlAT3 = 0 : nlAT3++; /* attributes3 */

				break;

			case KEY_UP:
				if     (nc == 0) (nlFG == 0)  ? nlFG =  7  : nlFG--; /* FG */
				else if(nc == 1) (nlBG == 0)  ? nlBG =  7  : nlBG--; /* BG */
				else if(nc == 2) (nlAT1 == 0) ? nlAT1 = 12 : nlAT1--; /* attributes1 */
				else if(nc == 3) (nlAT2 == 0) ? nlAT2 = 12 : nlAT2--; /* attributes2 */
				else             (nlAT3 == 0) ? nlAT3 = 12 : nlAT3--; /* attributes3 */

				break;

			case KEY_LEFT:
				if(nc == 0) nc = 4;
				else        nc--;

				break;

			case KEY_RIGHT:
				if(nc == 4) nc = 0;
				else        nc++;

				break;

			case KEY_END:
				break;
		}

	}while(keyPressed != KEY_END);

	curs_set(cursor);

	endwin();

	return(0);
}
