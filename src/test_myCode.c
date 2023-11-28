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
	
	if(has_colors()){
		start_color();
	}

	int lvl;
	lvl = splash_screen();

	int playerX, playerY;

	getmaxyx(win, max_y, max_x);

	int mid_y = max_y / 2;
	int mid_x = max_x / 2;

	playerX = (max_x / 2) - 3;
	playerY = (max_y / 2);

	if (lvl == 3) playerY -= 7;

	int *xLoc, *yLoc, *ZyLoc1, *ZxLoc1, *ZyLoc2, *ZxLoc2, *ZyLoc3, *ZxLoc3, *ZyLoc4, *ZxLoc4, key;
	xLoc = &playerX;
	yLoc = &playerY;

	// First Zombie
	int zombie1X = 5;
	int zombie1Y = 5;

	ZyLoc1 = &zombie1Y;
	ZxLoc1 = &zombie1X;


	// Second Zombie
	int zombie2X = max_x - 5;
	int zombie2Y = max_y - 5;

	ZyLoc2 = &zombie2Y;
	ZxLoc2 = &zombie2X;

	// Third Zombie
	int zombie3X = max_x - 5;
	int zombie3Y = 5;

	ZyLoc3 = &zombie3Y;
	ZxLoc3 = &zombie3X;

	// Fourth Zombie
	int zombie4X = 5;
	int zombie4Y = max_y - 5;

	ZyLoc4 = &zombie4Y;
	ZxLoc4 = &zombie4X;


	while(1){
		keypad(win, true);
		refresh();
		wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');

		// LEVEL 1
		if (lvl == 1 || lvl == 0){
			do{
			display_level(win, 1);
			int guntype = upgrade_box(win, 1, yLoc, xLoc);
			char gun[20] = "PISTOL";

			wattron(win, A_BOLD | A_REVERSE);

			if (guntype == 1){
				char gun[20] = "SHOT GUN";
			}
			else if (guntype == 2){
				char gun[20] = "RIFLE";
			}

			mvwprintw(win, 3, mid_x - 11, "GUN: %s", gun);
			wattroff(win, A_BOLD | A_REVERSE);

			printCharacter(win, 'P', yLoc, xLoc, 1);
			printEnemy(win, 'Z', ZyLoc1, ZxLoc1, 1);

			key = wgetch(win);
			printCharacter(win, ' ', yLoc, xLoc, 0);
			printEnemy(win, ' ', ZyLoc1, ZxLoc1, 0);
			moveCharacter(win, yLoc, xLoc, key);
			moveEnemy(win, ZyLoc1, ZxLoc1, yLoc, xLoc); 
			printCharacter(win, 'P', yLoc, xLoc, 1);
			printEnemy(win, 'Z', ZyLoc1, ZxLoc1, 1);
			
			wrefresh(win);

			if ((*yLoc == *ZyLoc1) && (*xLoc == *ZxLoc1)){
				key = 'o';
			}
			
			} while (key!= 'q' && key != 'p' && key != 'o');
		}	

		

		// LEVEL 2
		else if (lvl == 2){
                        do{
                        display_level(win, 2);
                        upgrade_box(win, 2, yLoc, xLoc);

                        printCharacter(win, 'P', yLoc, xLoc, 1);
			printEnemy(win, 'Z', ZyLoc1, ZxLoc1, 1);
                        printEnemy(win, 'Z', ZyLoc2, ZxLoc2, 1);

                        key = wgetch(win);

                        printCharacter(win, ' ', yLoc, xLoc, 0);
			printEnemy(win, ' ', ZyLoc1, ZxLoc1, 0);
                        printEnemy(win, ' ', ZyLoc2, ZxLoc2, 0);

                        moveCharacter(win, yLoc, xLoc, key);
			moveEnemy(win, ZyLoc1, ZxLoc1, yLoc, xLoc);
                        moveEnemy(win, ZyLoc2, ZxLoc2, yLoc, xLoc);

                        printCharacter(win, 'P', yLoc, xLoc, 1);
			printEnemy(win, 'Z', ZyLoc1, ZxLoc1, 1);
                        printEnemy(win, 'Z', ZyLoc2, ZxLoc2, 1);

                        wrefresh(win);

                        if (((*yLoc == *ZyLoc1) && (*xLoc == *ZxLoc1)) || ((*yLoc == *ZyLoc2) && (*xLoc == *ZxLoc2))) {
                                key = 'o';
                        }

                        } while (key!= 'q' && key != 'p' && key != 'o');
                }

			


		// LEVEL 3
		else if (lvl == 3){
			do{
                        display_level(win, 3);
                        upgrade_box(win, 3, yLoc, xLoc);
			int guntype = upgrade_box(win, 1, yLoc, xLoc);
                        char gun[20] = "PISTOL";

                        wattron(win, A_BOLD | A_REVERSE);

                        if (guntype == 1){
                                char gun[20] = "SHOT GUN";
                        }
                        else if (guntype == 2){
                                char gun[20] = "RIFLE";
                        }

                        mvwprintw(win, 3, mid_x - 11, "GUN: %s", gun);
                        wattroff(win, A_BOLD | A_REVERSE);

                        printCharacter(win, 'P', yLoc, xLoc, 1);
                        printEnemy(win, 'Z', ZyLoc1, ZxLoc1, 1);
                        printEnemy(win, 'Z', ZyLoc2, ZxLoc2, 1);
			printEnemy(win, 'Z', ZyLoc3, ZxLoc3, 1);

                        key = wgetch(win);

                        printCharacter(win, ' ', yLoc, xLoc, 0);
                        printEnemy(win, ' ', ZyLoc1, ZxLoc1, 0);
                        printEnemy(win, ' ', ZyLoc2, ZxLoc2, 0);
			printEnemy(win, ' ', ZyLoc3, ZxLoc3, 0);
			printEnemy(win, ' ', ZyLoc4, ZxLoc4, 0);


                        moveCharacter(win, yLoc, xLoc, key);
                        moveEnemy(win, ZyLoc1, ZxLoc1, yLoc, xLoc);
                        moveEnemy(win, ZyLoc2, ZxLoc2, yLoc, xLoc);
			moveEnemy(win, ZyLoc3, ZxLoc3, yLoc, xLoc);
			moveEnemy(win, ZyLoc4, ZxLoc4, yLoc, xLoc);

			

                        printCharacter(win, 'P', yLoc, xLoc, 1);
                        printEnemy(win, 'Z', ZyLoc1, ZxLoc1, 1);
                        printEnemy(win, 'Z', ZyLoc2, ZxLoc2, 1);
			printEnemy(win, 'Z', ZyLoc3, ZxLoc3, 1);
			printEnemy(win, 'Z', ZyLoc4, ZxLoc4, 1);

                        wrefresh(win);

                        if (((*yLoc == *ZyLoc1) && (*xLoc == *ZxLoc1)) || ((*yLoc == *ZyLoc2) && (*xLoc == *ZxLoc2)) || ((*yLoc == *ZyLoc3) && (*xLoc == *ZxLoc3)) || ((*yLoc == *ZyLoc3) && (*xLoc == *ZxLoc3))) {
                                key = 'o';
                        }

                        } while (key!= 'q' && key != 'p' && key != 'o');
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

		// GAME OVER
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
