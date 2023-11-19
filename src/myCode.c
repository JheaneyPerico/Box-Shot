#include <ncurses.h>

void splash_screen() {

	clear();
                      //_________     _____     ___   ___   ___       _______        _____  
	mvprintw(5,10, "_________     _____    ___   ___   ___     ______      _____    ");
	mvprintw(6,10, "|__   __|    /     \\   \\  \\  | |  /  /    |  ____|    |  _  \\  ");
	mvprintw(7,10, "   | |      |       |   \\  \\ | | /  /     | |____     | |_)  | ");
	mvprintw(8,10, "   | |      |       |    \\  \\| |/  /      | _____|    |  _  / ");
	mvprintw(9,10, "   | |      |       |     \\  \\ /  /       | |____     | | \\ \\");
	mvprintw(10,10, "   |_|       \\_____/       \\_____/        |______|    |_|  \\_\\");


	mvprintw(12, 10, "Welcome to Tower Defense!");
	mvprintw(14, 10, "Instructions");
	mvprintw(15, 10, "Select area: Arrow Keys");
	mvprintw(16,10, "Place tower: Spacebar");
	mvprintw(17,10, "Upgrade: Enter");
	mvprintw(32,47, " START");
	mvprintw(34,47, "LEVEL 1");
	mvprintw(36,47, "LEVEL 2");
	mvprintw(38,47, "LEVEL 3");

	refresh();


}
