#include <ncurses.h>

int splash_screen() {

	clear();
                      //_________     _____     ___   ___   ___       _______        _____  
	mvprintw(5,10, "_________     _____    ___   ___   ___     ______      _____    ");
	mvprintw(6,10, "|__   __|    /     \\   \\  \\  | |  /  /    |  ____|    |  _  \\  ");
	mvprintw(7,10, "   | |      |       |   \\  \\ | | /  /     | |____     | |_)  | ");
	mvprintw(8,10, "   | |      |       |    \\  \\| |/  /      | _____|    |  _  / ");
	mvprintw(9,10, "   | |      |       |     \\  \\ /  /       | |____     | | \\ \\");
	mvprintw(10,10, "   |_|       \\_____/       \\_____/        |______|    |_|  \\_\\");

	
	WINDOW *inputWin = newwin(11, 14, 30, 45);
	wborder(inputWin, '|', '|', '-', '-', '+', '+', '+', '+');
	

	refresh();
	wrefresh(inputWin);

	int xStr = 2, yStr = 2;

	mvwprintw(inputWin, yStr, xStr, "START");
	mvwprintw(inputWin, yStr + 2, xStr, "LEVEL 1");
	mvwprintw(inputWin, yStr + 4, xStr, "LEVEL 2");
	mvwprintw(inputWin, yStr + 6, xStr, "LEVEL 3");

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

	if (y == yStr + 2)
		return 1;

	else if (y == yStr + 4)
		return 2;

	else if (y == yStr + 6)
		return 3;


	return 0;


}

void Player(WINDOW *win){

	int playerX, playerY;

	int MAX_HEIGHT = 20;
	int MAX_WIDTH = 40;

	playerX = MAX_WIDTH / 2;
	playerY = MAX_HEIGHT / 2;

	if (playerX < 0) playerX = 0;
	if (playerX >= MAX_WIDTH) playerX = MAX_WIDTH - 1;
	if (playerY < 0) playerY = 0;
	if (playerY >= MAX_HEIGHT) playerY = MAX_HEIGHT - 1;

	mvprintw(playerY, playerX, "P");

	keypad(stdscr, true);

	int key = getch();

	while (key != '\n'){

		mvprintw(playerY, playerX, " ");

		switch(key) {
			case KEY_UP:
				playerY--;
				playerY--;
				break;

			case KEY_DOWN:
				playerY++;
				playerY++;
				break;

			case KEY_LEFT:
				playerX--;
				playerX--;
				break;

			case KEY_RIGHT:
				playerX++;
				playerX++;
				break;

			default:
				refresh();
				break;

		} 

		mvprintw(playerY, playerX, "P");

		refresh();

		key = getch();
	} 


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
	box(win, 0,0);

	WINDOW *box1 = newwin(mid_height - 15, mid_width - 45, start_y, start_x); // top left box
	WINDOW *box2 = newwin(mid_height - 15, mid_width - 45, (start_y * 2), (start_x * 2)); // middle box
	WINDOW *box3 = newwin(mid_height - 15, mid_width - 45, (start_y), (start_x * 3)); // bottom right box
	WINDOW *box4 = newwin(mid_height - 15, mid_width - 45, (start_y * 3), (start_x * 3)); // top right box
	WINDOW *box5 = newwin(mid_height - 15, mid_width - 45, (start_y * 3), (start_x));

	// Display level layout
	switch(lvl) {

		case 1:
			// Print lvl 1 layout
			//WINDOW *box1 = newwin(mid_height - 15, mid_with -45, start_y, start_x);
			box(box1, 0,0);
			box(box2, 0,0);
			box(box3, 0,0);
			box(box4, 0,0);
			box(box5, 0,0);

			refresh();

			wrefresh(win);
			wrefresh(box1);
			wrefresh(box2);
			wrefresh(box3);
			wrefresh(box4);
			wrefresh(box5);
			
			break;

		case 2:
			// Print lvl 2 layout
			box(box1, 0,0);
			box(box3, 0,0);

			refresh();

			wrefresh(win);
			wrefresh(box1);
			wrefresh(box2);
			wrefresh(box3);

			break;
			

		case 3: 
			// Print lvl 3 layout
			box(box1, 0,0);
			box(box2, 0,0);
			box(box3, 0,0);
			box(box4, 0,0);

			refresh();

			wrefresh(win);
			wrefresh(box1);
			wrefresh(box2);
			wrefresh(box3);
			wrefresh(box4);

			break;
	}

	refresh();
}

