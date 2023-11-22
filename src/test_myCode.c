#include <ncurses.h>
#include "myCode.h"
#include "character.h"

int main(){
	initscr();
	noecho();
	cbreak();
	
	int lvl;	
	lvl = splash_screen();

	int playerX, playerY;

	int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);

	playerX = (max_x / 2) - 3;
	playerY = (max_y / 2);

	if (lvl == 3) playerY -= 7;

	Character player = {playerX, playerY, "P1", playerX, playerY};

	while(1){
		// LEVEL 1
		if (lvl == 1 || lvl == 0){
			display_level(1);
			upgrade_box(1);
			Enemies(5,1);
			printCharacter(player);
			
			char key = getch();
			if (key != 'q')
				moveCharacter(&player, key);
		}

		// LEVEL 2
		else if (lvl == 2){
			printw("level 2");
			display_level(2);
			upgrade_box(2);
			Enemies(9,2);
		}

		// LEVEL 3
		else if (lvl == 3){
			printw("level 3");
			display_level(3);
			upgrade_box(3);
			Enemies(15,3);
		}
		refresh();

		char ch = getch();
		if (ch == 'q') break;

	}

	endwin();

	return 0;
}
