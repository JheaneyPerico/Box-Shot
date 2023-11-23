#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "character.h"
#define PLAYER "P1"
#define ENEMY "Zb"

int splash_screen() {

	clear();

	// COLOR RED -> PAIR(1)
	if (has_colors()){
		start_color();
		init_pair(1, COLOR_RED, A_NORMAL);
	}
	
	int max_x, max_y;
	getmaxyx(stdscr, max_x, max_y);

	int mid_height = max_y / 2;
	int mid_width = max_x / 2;

	// SPLASH SCREEN
	attron(A_BOLD);
	mvprintw(10, mid_width - 25, " ________  ________     ___    ___");
	mvprintw(11,mid_width - 25, "|\\   __  \\|\\   __  \\   |\\  \\  /  /|");
	mvprintw(12,mid_width - 25, "\\ \\  \\|\\ /\\ \\  \\|\\  \\  \\ \\  \\/  / /");
	mvprintw(13,mid_width - 25, " \\ \\   __  \\ \\  \\\\\\  \\  \\ \\    / /");
	mvprintw(14,mid_width - 25, "  \\ \\  \\|\\  \\ \\  \\\\\\  \\  /     \\/");
	mvprintw(15,mid_width - 25, "   \\ \\_______\\ \\_______\\/  /\\   \\");
	mvprintw(16,mid_width - 25, "    \\|_______|\\|_______/__/ /\\ __\\");
	mvprintw(17,mid_width - 25, "                       |__|/ \\|__|"); // 16

	attron(COLOR_PAIR(1)); // red
	mvprintw(10, mid_width + 25, " ________  ___  ___  ________  _________");
	mvprintw(11, mid_width + 25, "|\\       \\|\\  \\|\\  \\|\\   __  \\|\\___   ___\\");
	mvprintw(12, mid_width + 25, "\\ \\  \\___|\\ \\  \\\\\\  \\ \\  \\|\\  \\|___ \\  \\_|");
	mvprintw(13, mid_width + 25, " \\ \\_____  \\ \\   __  \\ \\  \\\\\\  \\   \\ \\  \\");
	mvprintw(14, mid_width + 25, "  \\|____|\\  \\ \\  \\ \\  \\ \\  \\\\\\  \\   \\ \\  \\");
	mvprintw(15, mid_width + 25, "    ____\\_\\  \\ \\__\\ \\__\\ \\_______\\   \\ \\__\\");
	mvprintw(16, mid_width + 25, "   |\\_________\\|__|\\|__|\\|_______|    \\|__|");
	mvprintw(17, mid_width + 25, "   \\|_________|"); // 58

	attroff(COLOR_PAIR(1));

	mvprintw(25, mid_width + strlen("WELCOME TO BOX SHOT")/2, "WELCOME TO BOX SHOT");
	mvprintw(27, mid_width + 2, "SELECT DIFFICULTY AND PRESS ENTER");
	attroff(A_BOLD);
	
	attron(A_DIM);
	mvprintw(31, 9, "INSTRUCTIONS:");
	mvprintw(33, 5, "MOVE USING ARROR KEYS");
	mvprintw(35, 5, "USE 'SPACE' TO SHOOT");
	mvprintw(37, 4, "COLLECT WEAPONS AND ITEMS");
	mvprintw(39, 3, "ELIMINATE ALL ZOMBIES TO WIN");
	attroff(A_DIM);

	// BORDER
	WINDOW *inputWin = newwin(11, 14, 30, 45);
	wborder(inputWin, '|', '|', '-', '-', '+', '+', '+', '+');
	

	refresh();
	wrefresh(inputWin);

	int xStr = 2, yStr = 2;

	// Add buttons
	mvwprintw(inputWin, yStr, xStr, "START");
	mvwprintw(inputWin, yStr + 2, xStr, "LEVEL 1");
	mvwprintw(inputWin, yStr + 4, xStr, "LEVEL 2");
	mvwprintw(inputWin, yStr + 6, xStr, "LEVEL 3");
	
	// Selecting button
	int x = 10, y = 2;
	mvwprintw(inputWin, y, x, "<");
	
	keypad(inputWin, true);

	int ch;

	refresh();
	wrefresh(inputWin);

	while((ch = wgetch(inputWin)) != '\n'){
		switch (ch) {
			case KEY_UP:
				if (y-2 > 0){
					//Clear current position
					mvwprintw(inputWin, y, x, " ");

					// Update position (move up)
					y--;
					y--;

					// Print string
					mvwprintw(inputWin, y,x, "<");

					wrefresh(inputWin);
				}
					break;

			case KEY_DOWN:

				if (y+2 < 9){
					//Clear current position
					mvwprintw(inputWin, y, x, " ");

					// Update position (move down)
					y++;
					y++;

					// Print string
					mvwprintw(inputWin, y, x, "<");

					wrefresh(inputWin);
				}
					break;

			default:
				wrefresh(inputWin);
				break;

		}

		refresh();
		wrefresh(inputWin);
	}

	refresh();

	// Level 1
	if (y == yStr + 2)
		return 1;

	// Level 2
	else if (y == yStr + 4)
		return 2;
	
	// Level 3
	else if (y == yStr + 6)
		return 3;


	return 0;


}

void printCharacter(WINDOW *win, Character character){

	if(has_colors()){
		start_color();
		init_pair(1, COLOR_BLACK, COLOR_GREEN);
	}

	wattron(win, COLOR_PAIR(1));

	mvwprintw(win, character.y, character.x, "%s", character.symbol);

	wattroff(win, COLOR_PAIR(1));
	refresh();
}

void moveCharacter(WINDOW *win, Character *character, int key){

	// MOVE PLAYER
	keypad(win, true);

	switch(key) {
		case KEY_UP:
			character->y--;
			break;

		case KEY_DOWN:
			character->y++;
			break;

		case KEY_LEFT:
			character->x--;
			break;

		case KEY_RIGHT:
			character->x++;
			break;

		default:
			refresh();
			break;
	} 

	wrefresh(win);
	return;


}

void Enemies(WINDOW *win, int MAX_ENEMIES, int lvl){

	int enemyX[MAX_ENEMIES], enemyY[MAX_ENEMIES];

	int max_y, max_x;
	getmaxyx(win, max_y, max_x);

	int mid_height = max_y / 2;
	int mid_width = max_x / 2;

	int start_y = (max_y - mid_height) / 2 - 2;
	int start_x = (max_x - mid_width) / 2 - 5;


	// COLOR RED -> PAIR(3)
	if (has_colors()){
		start_color();
		init_pair(3, COLOR_BLACK, COLOR_RED);
	}

		
	wattron(win,COLOR_PAIR(3));

	int count1 = 35 / lvl;
	int count2 = 35 / lvl;
	int count3 = 140 /lvl;
	int count4 = 140 / lvl;


	// LEFT
	for (int i = 0; i < floor(MAX_ENEMIES * 0.25); ++i){
		enemyX[i] = 5;
		enemyY[i] = count1;
		count1 += 20;
	}

	// RIGHT
	for (int i = floor(MAX_ENEMIES * 0.25); i < floor(MAX_ENEMIES * 0.5); ++i){
		enemyX[i] = max_x - 5;
		enemyY[i] = count2;
		count2 += 20;
	}

	// TOP
	for (int i = floor(MAX_ENEMIES * 0.5); i < floor(MAX_ENEMIES * 0.75); ++i){
		enemyX[i] = count3;
		enemyY[i] = 2;
		count3 += 40;

	}

	// BOTTOM
	for (int i = floor(MAX_ENEMIES * 0.75); i < MAX_ENEMIES; ++i){
		enemyX[i] = count4;
		enemyY[i] = max_y - 3;
		count4 += 40;
	}
	
	// Print Enemies
	for (int i = 0; i < MAX_ENEMIES; ++i){
		mvwprintw(win, enemyY[i], enemyX[i], ENEMY);
		wrefresh(win);
	}

	wattroff(win, COLOR_PAIR(3));
	wrefresh(win);


}

int upgrade_box(WINDOW *win, int MAX_NUM){

	int max_y, max_x;
	getmaxyx(win, max_y, max_x);

	int guntype;

	// COLOR YELLO -> PAIR(4)
	if (has_colors()){
		start_color();
		init_pair(4, COLOR_YELLOW, COLOR_YELLOW);
	}

	wattron(win, COLOR_PAIR(4)); // yellow
	switch(MAX_NUM) {
		case 1: // (lvl 1 -> 1 box)
			mvwprintw(win, max_y / 2 + 7, max_x / 4 + 5, "##");
			guntype = 1;
			break;

		case 2: // (lvl 2 -> 2 boxes)
			mvwprintw(win, max_y / 4 - 1, max_x / 3 + 5, "##");
			mvwprintw(win, max_y / 2 + 8, max_x / 2 + 6, "##");
			guntype = 2;
			break;

		case 3: // (lvl 3 -> 3 boxes)
			mvwprintw(win, max_y / 4 - 1, max_x / 3 + 5, "##");
			mvwprintw(win, max_y / 2 + 3, max_x / 2 + 23, "##");
			mvwprintw(win, max_y / 2 + 8, max_x / 2 - 5, "##");
			guntype = 3;
			break;

	}

	wattroff(win, COLOR_PAIR(4));

	wrefresh(win);

	return guntype;

}

void display_level(WINDOW *win, int lvl){

	int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);
	
	int mid_height = max_y / 2;
	int mid_width = max_x / 2;

	int start_y = (max_y - mid_height) / 2 - 2;
	int start_x = (max_x - mid_width) / 2 - 5;

	// CREATE BOXES (WALL)
	WINDOW *box1 = newwin(10, 20, start_y, start_x); // top left box
	WINDOW *box2 = newwin(10, 20, (start_y * 2), (start_x * 2)); // middle box
	WINDOW *box3 = newwin(10, 20, (start_y), (start_x * 3)); // top right box
	WINDOW *box4 = newwin(10, 20, (start_y * 3), (start_x * 3)); // bottom right box
	WINDOW *box5 = newwin(10, 20, (start_y * 3), (start_x)); // bottom left box

	// WHITE COLOR -> Pair(2)
	if (has_colors()){
		start_color();
		init_pair(2, COLOR_WHITE, COLOR_WHITE);
	}


	// Display level layout
	switch(lvl) {

		case 1:
			// Print lvl 1 layout
			wattron(win, A_BOLD);
			mvwprintw(win, 2, 2, "LEVEL 1");
			wattroff(win, A_BOLD);

			// COLOR THE BOXES TO WHITE		
			wattron(box1, COLOR_PAIR(2));
			wattron(box4, COLOR_PAIR(2));

			// ADD BOXES
			box(box1, 0,0);
			box(box4,0,0);
	
			// FILL BOXES WITH WHITE SPACE
			for (int i = 1; i <  (mid_height - 15); ++i){
				for (int j = 1; j < (mid_width - 45); ++j){
					mvwaddch(box1, i, j, ' ');
					mvwaddch(box4, i, j, ' ');

				}
			}

			// TURN OFF COLOR
			wattroff(box1, COLOR_PAIR(2));
			wattroff(box4, COLOR_PAIR(2));

			// REFRESH
			refresh();

			wrefresh(win);
			wrefresh(box1);
			wrefresh(box4);

			break;

		case 2:
			// Print lvl 2 layout
			wattron(win, A_BOLD);
			mvwprintw(win, 2, 2, "LEVEL 2");
			wattroff(win, A_BOLD);

			// COLOR THE BOXES TO WHITE
			wattron(box1, COLOR_PAIR(2));
			wattron(box3, COLOR_PAIR(2));
			wattron(box4, COLOR_PAIR(2));
			wattron(box5, COLOR_PAIR(2));
				
			// ADD BOXES
			box(box1, 0,0);
			box(box3, 0,0);
			box(box4, 0,0);
			box(box5,0,0);

			// FILL BOXES WITH WHITE SPACE
			for (int i = 1; i < (mid_height - 15); ++i){
				for (int j = 1; j < (mid_width - 45); ++j){
					mvwaddch(box1, i, j, ' ');
					mvwaddch(box3, i, j, ' ');
					mvwaddch(box4, i, j, ' ');
					mvwaddch(box5, i, j, ' ');
				}
			}
			
			// TURN OFF COLOR
			wattroff(box1, COLOR_PAIR(2));
			wattroff(box3, COLOR_PAIR(2));
			wattroff(box4, COLOR_PAIR(2));
			wattroff(box5, COLOR_PAIR(2));

			// REFRESH
			refresh();

			wrefresh(win);
			wrefresh(box1);
			wrefresh(box3);
			wrefresh(box4);
			wrefresh(box5);

			break;
			

		case 3: 
			// Print lvl 3 layout
			wattron(win, A_BOLD);
			mvwprintw(win, 2, 2, "LEVEL 3");
			wattroff(win, A_BOLD);
					
			// BOXES COLOR	
			wattron(box1, COLOR_PAIR(2));
			wattron(box2, COLOR_PAIR(2));
			wattron(box3, COLOR_PAIR(2));
			wattron(box4, COLOR_PAIR(2));
			wattron(box5, COLOR_PAIR(2));


			// ADD BOXES
			box(box1, 0,0);
			box(box2, 0,0);
			box(box3, 0,0);
			box(box4, 0,0);
			box(box5, 0,0);

			// FILL BOXES WITH WHITE SPACE
			for (int i = 1; i < (mid_height); ++i){
				for (int j = 1; j < (mid_width); ++j){
					mvwaddch(box1, i, j, ' ');
					mvwaddch(box2, i, j, ' ');
					mvwaddch(box3, i, j, ' ');
					mvwaddch(box4, i, j, ' ');
					mvwaddch(box5, i, j, ' ');
				}
			}

			// TURN OFF COLOR
			wattroff(box1, COLOR_PAIR(2));
			wattroff(box2, COLOR_PAIR(2));
			wattroff(box3, COLOR_PAIR(2));
			wattroff(box4, COLOR_PAIR(2));
			wattroff(box5, COLOR_PAIR(2));

			// REFRESH
			refresh();

			wrefresh(win);
			wrefresh(box1);
			wrefresh(box2);
			wrefresh(box3);
			wrefresh(box4);
			wrefresh(box5);

			break;
	}
	

	wrefresh(win);
	refresh();
}
/*
void pause_screen(){
	clear();

	mvprintw(2, 10," _________  ___  ___  _______           ________  ________  _____ ______   _______           ___  ________           ________  ________  ___  ___  ________  _______   ________     ");
	mvprintw(4,10, "|\\___   ___\\\\  \\|\\  \\|\\  ___ \\         |\\   ____\\|\\   __  \\|\\   _ \\  _   \\|\\  ___ \         |\\  \\|\\   ____\\         |\\   __  \\|\\   __  \\|\\  \\|\\  \\|\\   ____\\|\\  ___ \\ |\\   ___ \\    ");
	mvprintw(6,10, "\\|___ \\  \\_\\ \\  \\\\\\  \\ \\   __/|        \\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\\\__\\ \\  \\ \\   __/|        \\ \\  \\ \\  \\___|_        \\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\\\\\  \\ \\  \\___|\\ \\   __/|\\ \\  \\_|\\ \\   ");
	mvprintw(8,10, "     \\ \\  \\ \\ \\   __  \\ \\  \\_|/__       \\ \\  \\  __\\ \\   __  \\ \\  \\\\|__| \\  \\ \\  \\_|/__       \\ \\  \\ \\_____  \\        \\ \\   ____\\ \\   __  \\ \\  \\\\\\  \\ \\_____  \\ \\  \\_|/_\\ \\  \\ \\\\ \\  ");
	mvprintw(10,10,"      \\ \\  \\ \\ \\  \\ \\  \\ \\  \\_|\\ \\       \\ \\  \\|\\  \\ \\  \\ \\  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\       \\ \\  \\|____|\\  \\        \\ \\  \\___|\\ \\  \\ \\  \\ \\  \\\\\\  \\|____|\\  \\ \\  \\_|\\ \\ \\  \\_\\\\ \\ ");
	mvprintw(12,10,"       \\ \\__\\ \\ \\__\\ \\__\\ \\_______\\       \\ \\_______\\ \\__\\ \__\\ \\__\\    \\ \\__\\ \\_______\\       \\ \\__\\____\\_\\  \\        \\ \\__\\    \\ \\__\\ \\__\\ \\_______\\____\\_\\  \\ \\_______\\ \\_______\\");
	mvprintw(14,10,"        \\|__|  \\|__|\\|__|\\|_______|        \\|_______|\\|__|\\|__|\\|__|     \\|__|\\|_______|        \\|__|\\_________\\        \\|__|     \\|__|\\|__|\\|_______|\_________\\|_______|\\|_______|");
	mvprintw(16,10,"                                                                                                    \\|_________|                                     \\|_________|                   ");

	refresh();

}
*/
