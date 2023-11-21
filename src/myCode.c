#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define PLAYER "P1"
#define ENEMY "Zb"

int splash_screen() {

	clear();

	// COLOR RED -> PAIR(1)
	if (has_colors()){
		start_color();
		init_pair(1, COLOR_RED, A_NORMAL);
	}
	
	// SPLASH SCREEN
	attron(A_BOLD);
	mvprintw(10,10, " ________  ________     ___    ___");
	mvprintw(11,10, "|\\   __  \\|\\   __  \\   |\\  \\  /  /|");
	mvprintw(12,10, "\\ \\  \\|\\ /\\ \\  \\|\\  \\  \\ \\  \\/  / /");
	mvprintw(13,10, " \\ \\   __  \\ \\  \\\\\\  \\  \\ \\    / /");
	mvprintw(14,10, "  \\ \\  \\|\\  \\ \\  \\\\\\  \\  /     \\/");
	mvprintw(15,10, "   \\ \\_______\\ \\_______\\/  /\\   \\");
	mvprintw(16,10, "    \\|_______|\\|_______/__/ /\\ __\\");
	mvprintw(17,10, "                       |__|/ \\|__|");

	attron(COLOR_PAIR(1)); // red
	mvprintw(10, 58, " ________  ___  ___  ________  _________");
	mvprintw(11, 58, "|\\       \\|\\  \\|\\  \\|\\   __  \\|\\___   ___\\");
	mvprintw(12, 58, "\\ \\  \\___|\\ \\  \\\\\\  \\ \\  \\|\\  \\|___ \\  \\_|");
	mvprintw(13, 58, " \\ \\_____  \\ \\   __  \\ \\  \\\\\\  \\   \\ \\  \\");
	mvprintw(14, 58, "  \\|____|\\  \\ \\  \\ \\  \\ \\  \\\\\\  \\   \\ \\  \\");
	mvprintw(15, 58, "    ____\\_\\  \\ \\__\\ \\__\\ \\_______\\   \\ \\__\\");
	mvprintw(16, 58, "   |\\_________\\|__|\\|__|\\|_______|    \\|__|");
	mvprintw(17, 58, "   \\|_________|");

	attroff(COLOR_PAIR(1));

	mvprintw(25, 43, "WELCOME TO BOX SHOT");
	mvprintw(27, 36, "SELECT DIFFICULTY AND PRESS ENTER");
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

int Player(int lvl){

	int playerX, playerY;
	
	int MAX_HEIGHT, MAX_WIDTH;
	getmaxyx(stdscr, MAX_HEIGHT, MAX_WIDTH);

	playerX = (MAX_WIDTH / 2) - 3;
	playerY = MAX_HEIGHT / 2;

	// Have player position slightly up for level 3
	if (lvl == 3){
		playerY -= 7;
	}

	// Make Player inside bound
	if (playerX < 1) playerX = 1;
	if (playerX >= MAX_WIDTH) playerX = MAX_WIDTH - 1;
	if (playerY < 1) playerY = 1;
	if (playerY >= MAX_HEIGHT) playerY = MAX_HEIGHT - 1;

	// GREEN COLOR -> PAIR(1)
	if (has_colors()){
		start_color();
		init_pair(1, COLOR_BLACK, COLOR_GREEN);
	}

	attron(COLOR_PAIR(1)); // green
	mvprintw(playerY, playerX, PLAYER);
	attroff(COLOR_PAIR(1));

	keypad(stdscr, true);

	int key = getch();

	while (key != '\n'){

		// CLEAR CURRENT POSITION
		mvprintw(playerY, playerX, "  ");
		
		// MOVE PLAYER
		switch(key) {
			case KEY_UP:
				playerY--;
				break;

			case KEY_DOWN:
				playerY++;
				break;

			case KEY_LEFT:
				playerX--;
				break;

			case KEY_RIGHT:
				playerX++;
				break;

			default:
				refresh();
				break;

		} 

		attron(COLOR_PAIR(1));
		mvprintw(playerY, playerX, "P1");
		attroff(COLOR_PAIR(1));

		refresh();

		key = getch();

		
	} 

	return 0;



}

void Enemies(int MAX_ENEMIES){

	int enemyX[MAX_ENEMIES], enemyY[MAX_ENEMIES];

	int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);


	int start_x = (max_x - (max_x / 2)) / 2 - 12;
	int start_y = (max_y - (max_y / 2)) / 2 - 2;

	srand(time(NULL));
	
	// Have Enemies randomly spawn outside the box range
	for (int i = 0; i < MAX_ENEMIES; ++i){
		enemyX[i] = rand() % (max_x); //(1 to max_x)
		enemyY[i] = rand() % (max_y); // (1 to max_y)
		
		if ((enemyY[i] >= start_y && enemyY[i] <= start_y + 25) && (enemyX[i] >= start_x && enemyX[i] <= start_x + 80)){
			while ((enemyX[i] > start_x) && (enemyX[i] < (start_x + 80)))
				enemyX[i] = rand() % (max_x);

			while ((enemyY[i] >= start_y) && (enemyY[i] <= (start_y + 25)))
				enemyY[i] = rand() % (max_y);
				}
		}

	// COLOR RED -> PAIR(3)
	if (has_colors()){
		start_color();
		init_pair(3, COLOR_BLACK, COLOR_RED);
	}

	attron(COLOR_PAIR(3)); // red

	for (int i = 0; i < MAX_ENEMIES; ++i){
		mvprintw(enemyY[i], enemyX[i], "Zb");
		refresh();
	}

	attroff(COLOR_PAIR(3));
	refresh();


}

int upgrade_box(int MAX_NUM){

	int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);

	int guntype;

	// COLOR YELLO -> PAIR(4)
	if (has_colors()){
		start_color();
		init_pair(4, COLOR_YELLOW, COLOR_YELLOW);
	}

	attron(COLOR_PAIR(4)); // yellow
	switch(MAX_NUM) {
		case 1: // (lvl 1 -> 1 box)
			mvprintw(max_y / 2 + 7, max_x / 4 + 5, "##");
			guntype = 1;
			break;

		case 2: // (lvl 2 -> 2 boxes)
			mvprintw(max_y / 4 - 1, max_x / 3 + 5, "##");
			mvprintw(max_y / 2 + 8, max_x / 2 + 6, "##");
			guntype = 2;
			break;

		case 3: // (lvl 3 -> 3 boxes)
			mvprintw(max_y / 4 - 1, max_x / 3 + 5, "##");
			mvprintw(max_y / 2 + 3, max_x / 2 + 23, "##");
			mvprintw(max_y / 2 + 8, max_x / 2 - 5, "##");
			guntype = 3;
			break;

	}

	attroff(COLOR_PAIR(4));

	refresh();

	return guntype;

}

void display_level(int lvl){
	clear();

	int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);
	
	int mid_height = max_y / 2;
	int mid_width = max_x / 2;

	int start_y = (max_y - mid_height) / 2 - 2;
	int start_x = (max_x - mid_width) / 2 - 5;

	WINDOW *win = newwin(max_y, max_x, 0, 0);
	wborder(win, '|', '|', '-', '-', '+', '+', '+', '+'); // display the boundaries

	// CREATE BOXES (WALL)
	WINDOW *box1 = newwin(mid_height - 15, mid_width - 45, start_y, start_x); // top left box
	WINDOW *box2 = newwin(mid_height - 15, mid_width - 45, (start_y * 2), (start_x * 2)); // middle box
	WINDOW *box3 = newwin(mid_height - 15, mid_width - 45, (start_y), (start_x * 3)); // top right box
	WINDOW *box4 = newwin(mid_height - 15, mid_width - 45, (start_y * 3), (start_x * 3)); // bottom right box
	WINDOW *box5 = newwin(mid_height - 15, mid_width - 45, (start_y * 3), (start_x)); // bottom left box

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
			for (int i = 1; i < (mid_height - 15); ++i){
				for (int j = 1; j < (mid_width - 45); ++j){
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

