#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include "myCode.h"
#include "character.h"
#include <unistd.h>
#define DELAY_MICROSECONDS 1000000 // 1 second delay

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

	int *xLoc, *yLoc, *ZyLoc, *ZxLoc, key;
	xLoc = &playerX;
	yLoc = &playerY;

	int zombieX = 5;
	int zombieY = 5;
	ZyLoc = &zombieX;
	ZxLoc = &zombieY;

	while(1){
		keypad(win, true);
		refresh();
		wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');

		// LEVEL 1
		if (lvl == 1 || lvl == 0){
			do{
			display_level(win, 1);
			upgrade_box(win, 1);
		//	printEnemies(win,5, ZyLoc, ZxLoc);
			//Enemies(win, 5, 1, yLoc, xLoc);

			printCharacter(win, 'P', yLoc, xLoc, 1);
			printEnemy(win, 'Z', ZyLoc, ZxLoc, 1);

			key = wgetch(win);
			printCharacter(win, ' ', yLoc, xLoc, 0);
			printEnemy(win, ' ', ZyLoc, ZxLoc, 0);
			moveCharacter(win, yLoc, xLoc, key);
			moveEnemy(win, ZyLoc, ZxLoc, yLoc, xLoc); 
			printCharacter(win, 'P', yLoc, xLoc, 1);
			printEnemy(win, 'Z', ZyLoc, ZxLoc, 1);
			
			wrefresh(win);

			if ((*yLoc == *ZyLoc) && (*xLoc == *ZxLoc)){
				key = 'o';
			}
			
			} while (key!= 'q' && key != 'p' && key != 'o');
		}	

		

		// LEVEL 2
		else if (lvl == 2){
			do{
			display_level(win, 2);
			upgrade_box(win, 2);
			//Enemies(win, 9, 2, yLoc, xLoc);

			printCharacter(win, 'P', yLoc, xLoc, 1);

			key = wgetch(win);
			printCharacter(win, ' ', yLoc, xLoc, 0);
			moveCharacter(win, yLoc, xLoc, key);
			printCharacter(win, 'P', yLoc, xLoc, 1);

			wrefresh(win);
			} while (key!= 'q' && key != 'p');

		}

		// LEVEL 3
		else if (lvl == 3){
			do{
			display_level(win, 3);
			upgrade_box(win, 3);
			//Enemies(win, 15,3, yLoc, xLoc);

			printCharacter(win, 'P', yLoc, xLoc, 1);

			key = wgetch(win);
			printCharacter(win, ' ', yLoc, xLoc, 0);
			moveCharacter(win, yLoc, xLoc, key);
			printCharacter(win, 'P', yLoc, xLoc, 1);

			wrefresh(win);
			} while (key != 'q' && key != 'p');

		}
		refresh();
	
			
		int y_n;

		// QUIT PRESSED
		if (key == 'q'){
			werase(win);
			wrefresh(win);
			char ch;
			

			mvwprintw(win, mid_y, mid_x - 10, "DO YOU WANT TO QUIT? y/n");
			wrefresh(win);
				
			do {
				ch = wgetch(win);

				if (ch == 'y'){
					y_n = 1;
					break;
				}
				if (ch == 'n'){
					y_n = 0;
					mvwprintw(win, mid_y, mid_x - 10, "                        ");
					wrefresh(win);
					break;
					
				}
			} while(ch != 'n' || ch != 'y');

			if (y_n == 1)
				break;

		}	

	
		// PAUSE PRESSED
		if (key == 'p'){
			werase(win);
			wrefresh(win);

			char ch;


			mvwprintw(win, mid_y, mid_x - 20, "THE GAME IS PAUSED (press p to unpause)");
			wrefresh(win);

			do{
				ch = wgetch(win);

				if (ch == 'p'){
					mvwprintw(win, mid_y, mid_x - 20, "                                       ");
					break;
				}

			} while (ch != 'p');
		}

		if (key == 'o'){
			werase(win);
			wrefresh(win);
			mvwprintw(win, mid_y, mid_x - 5, "GAME OVER");
			mvwprintw(win, mid_y + 2, mid_x - 11, "PRESS ANY KEY TO EXIT ");

			char ch = wgetch(win);
			break;
		}
	
		refresh();

	}

	endwin();

	return 0;
}
