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

	int *hit1, *hit2, *hit3, *hit4, *quit;

	int collide1 = 0, collide2 = 0, collide3 = 0, collide4 = 0, exit = 0;

	hit1 = &collide1;
	hit2 = &collide2;
	hit3 = &collide3;
	hit4 = &collide4;
	quit = &exit;

	int nkey;

	if (lvl == 1)
		while(1){
			display_level(win, 1, ZyLoc1, ZxLoc1, yLoc, xLoc, hit1);
                        }

	while(1){
		keypad(win, true);
		refresh();
		wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
		char direction = 'r';

		// LEVEL 1
		if (lvl == 1 || lvl == 0){
			//while (*quit != 1){
			//	display_level(win, 1, ZyLoc1, ZxLoc1, yLoc, xLoc, hit1, quit);
			//}
			do{
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
//			printEnemy(win, 'Z', ZyLoc1, ZxLoc1, 1, hit1);

			key = wgetch(win);
			bullet(win, ZyLoc1, ZxLoc1, yLoc, xLoc, &direction, key);
			printCharacter(win, ' ', yLoc, xLoc, 0);
//			printEnemy(win, ' ', ZyLoc1, ZxLoc1, 0, hit1);
			moveCharacter(win, yLoc, xLoc, &direction, key);
//			moveEnemy(win, ZyLoc1, ZxLoc1, yLoc, xLoc); 
			printCharacter(win, 'P', yLoc, xLoc, 1);
//			printEnemy(win, 'Z', ZyLoc1, ZxLoc1, 1, hit1);
			
			wrefresh(win);

			if ((*yLoc == *ZyLoc1) && (*xLoc == *ZxLoc1)){
				if (*hit1 == 0){
					nkey = 'o';
				}
			}

			if(*hit1 == 1){
				nkey = 'n';
			}
			
			} while (key!= 'q' && key != 'p' && nkey != 'o' && nkey != 'n');
		}	

		

		// LEVEL 2
		else if (lvl == 2){
                        do{
                        display_level(win, 1, ZyLoc1, ZxLoc1, yLoc, xLoc, hit1);
                        upgrade_box(win, 2, yLoc, xLoc);

                        printCharacter(win, 'P', yLoc, xLoc, 1);
			printEnemy(win, 'Z', ZyLoc1, ZxLoc1, 1, hit1);
                        printEnemy(win, 'Z', ZyLoc2, ZxLoc2, 1, hit2);

                        key = wgetch(win);
			bullet(win, ZyLoc1, ZxLoc1, yLoc, xLoc, &direction, key);
                        printCharacter(win, ' ', yLoc, xLoc, 0);
			printEnemy(win, ' ', ZyLoc1, ZxLoc1, 0, hit1);
                        printEnemy(win, ' ', ZyLoc2, ZxLoc2, 0, hit2);

                        moveCharacter(win, yLoc, xLoc, &direction, key);
			moveEnemy(win, ZyLoc1, ZxLoc1, yLoc, xLoc);
                        moveEnemy(win, ZyLoc2, ZxLoc2, yLoc, xLoc);

                        printCharacter(win, 'P', yLoc, xLoc, 1);
			printEnemy(win, 'Z', ZyLoc1, ZxLoc1, 1, hit1);
                        printEnemy(win, 'Z', ZyLoc2, ZxLoc2, 1, hit2);

                        wrefresh(win);
			
			
                        if ((*yLoc == *ZyLoc1) && (*xLoc == *ZxLoc1)) {
				if (*hit1 == 0){
                                	nkey = 'o';
				}

			}

			if ((*yLoc == *ZyLoc2) && (*xLoc == *ZxLoc2)){
				if (*hit2 == 0){
					nkey = 'o';
				}
			}

			if (*hit1 == 1 && *hit2 == 1){
				nkey = 'n';
			}

                        } while (key!= 'q' && key != 'p' && nkey != 'o' && nkey != 'n');
                }

			


		// LEVEL 3
		else if (lvl == 3){
			do{
                        display_level(win, 1, ZyLoc1, ZxLoc1, yLoc, xLoc, hit1);
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
                        printEnemy(win, 'Z', ZyLoc1, ZxLoc1, 1, hit1);
                        printEnemy(win, 'Z', ZyLoc2, ZxLoc2, 1, hit2);
			printEnemy(win, 'Z', ZyLoc3, ZxLoc3, 1, hit3);
			printEnemy(win, 'Z', ZyLoc4, ZxLoc4, 1, hit4);

                        key = wgetch(win);
			bullet(win, ZyLoc1, ZxLoc1, yLoc, xLoc, &direction, key);

                        printCharacter(win, ' ', yLoc, xLoc, 0);
                        printEnemy(win, ' ', ZyLoc1, ZxLoc1, 0, hit1);
                        printEnemy(win, ' ', ZyLoc2, ZxLoc2, 0, hit2);
			printEnemy(win, ' ', ZyLoc3, ZxLoc3, 0, hit3);
			printEnemy(win, ' ', ZyLoc4, ZxLoc4, 0, hit4);


                        moveCharacter(win, yLoc, xLoc, &direction, key);
                        moveEnemy(win, ZyLoc1, ZxLoc1, yLoc, xLoc);
                        moveEnemy(win, ZyLoc2, ZxLoc2, yLoc, xLoc);
			moveEnemy(win, ZyLoc3, ZxLoc3, yLoc, xLoc);
			moveEnemy(win, ZyLoc4, ZxLoc4, yLoc, xLoc);

			

                        printCharacter(win, 'P', yLoc, xLoc, 1);
                        printEnemy(win, 'Z', ZyLoc1, ZxLoc1, 1, hit1);
                        printEnemy(win, 'Z', ZyLoc2, ZxLoc2, 1, hit2);
			printEnemy(win, 'Z', ZyLoc3, ZxLoc3, 1, hit3);
			printEnemy(win, 'Z', ZyLoc4, ZxLoc4, 1, hit4);

                        wrefresh(win);

                        if ((*yLoc == *ZyLoc1) && (*xLoc == *ZxLoc1)) {
				if (*hit1 == 0){
                                	nkey = 'o';
				}
                        }

			if ((*yLoc == *ZyLoc2) && (*xLoc == *ZxLoc2)){
				if (*hit2 == 0){
					nkey = 'o';
				}

			}

			if  ((*yLoc == *ZyLoc3) && (*xLoc == *ZxLoc3)){
				if (*hit3 == 0){
					nkey = 'o';
				}
			}

			if ((*yLoc == *ZyLoc4) && (*xLoc == *ZxLoc4)){
				if (*hit4 == 0){
					nkey = 'o';
				}
			}

			if (*hit1 == 1 && *hit2 == 1 && *hit3 == 1 && *hit4 == 1){
				nkey = 'w';
			}

                        } while (key!= 'q' && key != 'p' && nkey != 'o' && nkey != 'w');
                }



		refresh();
	
			
		int y_n;

		// QUIT PRESSED
		if (key == 'q'){
			werase(win);
			wrefresh(win);
			char ch;
			

			*quit = 1;

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
		if (nkey == 'o'){
			werase(win);
			wrefresh(win);
			mvwprintw(win, mid_y, mid_x - 5, "GAME OVER");
			mvwprintw(win, mid_y + 2, mid_x - 11, "PRESS ANY KEY TO EXIT ");

			char ch = wgetch(win);
			break;
		}

		if (nkey == 'n'){
			// REINITIALIZE VALUES TO RESET POTISION
			werase(win);
			wrefresh(win);
			mvwprintw(win, mid_y, mid_x - 10, "YOU BEAT THIS LEVEL!");
			mvwprintw(win, mid_y + 2, mid_x-20, "PRESS ANY KEY TO GO TO THE NEXT LEVEL ");
			char ch = wgetch(win);
			lvl += 1;

			playerX = (max_x / 2) - 3;
			playerY = (max_y / 2);

			if (lvl == 3) playerY -= 7;

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

			*hit1 = 0;
			*hit2 = 0;
			*hit3 = 0;
			*hit4 = 0;

			nkey = 0;

			werase(win);
			wrefresh(win);
			continue;
			
		}

		if (nkey == 'w'){
			werase(win);
			wrefresh(win);
			mvwprintw(win, mid_y, mid_x - 5, "YOU WIN!");
			wrefresh(win);

			int winch = getch();
			break;

		}
	
		refresh();

	}

	endwin();

	return 0;
}
