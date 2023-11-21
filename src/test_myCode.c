#include <ncurses.h>
#include "myCode.h"

int main(){

	initscr();
	noecho();
	cbreak();
	
	int lvl;	
	lvl = splash_screen();

	// LEVEL 1
	if (lvl == 1 || lvl == 0){
		display_level(1);
		upgrade_box(1);
		Enemies(2);
		Player(1);
	}

	// LEVEL 2
	else if (lvl == 2){
		printw("level 2");
		display_level(2);
		upgrade_box(2);
		Enemies(5);
		Player(2);
	}

	// LEVEL 3
	else if (lvl == 3){
		printw("level 3");
		display_level(3);
		upgrade_box(3);
		Enemies(10);
		Player(3);
	}

	refresh();

	getchar();

	endwin();
	return 0;
}
