#include <ncurses.h>
/*
typedef struct {
	int x;
	int y;
	char symbol[20];
	int initial_x;
	int initial_y;
} Character;
*/
void printCharacter(WINDOW *win, int *yLoc, int *xLoc);
void moveCharacter(WINDOW *win, int *yLoc, int *xLoc, int key);
