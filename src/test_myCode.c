#include <ncurses.h>
#include "myCode.h"
#include "character.h"

int main(){
	initscr();
	noecho();
	cbreak();

	int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);

	WINDOW *win = newwin(max_y, max_x, 0,0);

	int lvl;
	lvl = splash_screen();

	int playerX, playerY;

	getmaxyx(win, max_y, max_x);

	playerX = (max_x / 2) - 3;
	playerY = (max_y / 2);

	if (lvl == 3) playerY -= 7;

	Character player = {playerX, playerY, "P1", playerX, playerY};
	


	while(1){
		clear();
		wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
		refresh();

		// LEVEL 1
		if (lvl == 1 || lvl == 0){
			display_level(win, 1);
			upgrade_box(win, 1);
			Enemies(win, 5, 1);
			printCharacter(win, player);

			char key = wgetch(win);
			if (key != 'q'){
				moveCharacter(win, &player, key);
				printCharacter(win, player);
				mvwprintw(win, 5,5, "I will again write this sentence to see if this works");
			}
			wrefresh(win);
		}

		

		// LEVEL 2
		else if (lvl == 2){
			display_level(win, 2);
			upgrade_box(win, 2);
			Enemies(win, 9, 2);
		}

		// LEVEL 3
		else if (lvl == 3){
			display_level(win, 3);
			upgrade_box(win, 3);
			Enemies(win, 15,3);
		}
		refresh();

		char ch = getch();
		if (ch == 'q') break;
		/*moveCharacter(&player, ch);
		mvprintw(5, 5, "I will write this sentence to see if this works");
		*/
		refresh();

	}

	endwin();

	return 0;
}
