#include <ncurses.h>
#include "myCode.h"

int main(){

	initscr();
	noecho();
	cbreak();


	splash_screen();

	getchar();

	endwin();
	return 0;
}
