#include <ncurses.h>
#include "myCode.h"

int main(){

	initscr();
	noecho();
	cbreak();
	
	int lvl;	
	lvl = splash_screen();

	if (lvl == 1){
		printw("level 1");
		display_level(1);
	}
	else if (lvl == 2){
		printw("level 2");
		//put level 2 code here
	}
	else if (lvl == 3){
		printw("level 3");
		//put level 3 code here
	}

	refresh();

	getchar();

	endwin();
	return 0;
}
