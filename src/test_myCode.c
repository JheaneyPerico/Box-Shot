#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
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

	int mid_y = max_y / 2;
	int mid_x = max_x / 2;

	playerX = (max_x / 2) - 3;
	playerY = (max_y / 2);

	if (lvl == 3) playerY -= 7;

	int *xLoc, *yLoc, charL = 2, key;
	xLoc = &playerX;
	yLoc = &playerY;

	while(1){
		keypad(win, true);
		refresh();
		wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
		// LEVEL 1
		if (lvl == 1 || lvl == 0){
			do{
			display_level(win, 1);
			upgrade_box(win, 1);
			Enemies(win, 5, 1);

			printCharacter(win, "P1", yLoc, xLoc, 1);

			key = wgetch(win);
			printCharacter(win, "  ", yLoc, xLoc, 0);
			moveCharacter(win, yLoc, xLoc, key);
			printCharacter(win, "P1", yLoc, xLoc, 1);

			wrefresh(win);
			} while (key!= 'q') ;
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

	
		int y_n;

		if (key == 'q'){
			clear();
			char ch;
			

			mvwprintw(win, mid_y, mid_x - 5, "DO YOU WANT TO QUIT? y/n");
			wrefresh(win);
				
			do {
				ch = wgetch(win);

				if (ch == 'y'){
					y_n = 1;
					break;
				}
				if (ch == 'n'){
					y_n = 0;
					mvwprintw(win, mid_y, mid_x - 5, "                        ");
					wrefresh(win);
					break;
					
				}
			} while(ch != 'n' || ch != 'y');

			if (y_n == 1)
				break;

		}	

	

		if (key == 'p'){
			clear();
			char ch;


			mvwprintw(win, mid_x, mid_y - 10, "THE GAME IS PAUSED (press p to unpause");
			wrefresh(win);

			do{
				ch = wgetch(win);

				if (ch == 'p')
					break;

			} while (ch != 'p');
		}
	
		refresh();

	}

	endwin();

	return 0;
}
