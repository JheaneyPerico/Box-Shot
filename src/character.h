#include <ncurses.h>
void printCharacter(WINDOW *win, char symbol, int *yLoc, int *xLoc, int type);
void moveCharacter(WINDOW *win, int *yLoc, int *xLoc, char *dir, int key);
void printEnemy(WINDOW *win, char symbol, int *ZyLoc, int *ZxLoc, int type, int *hit);
void moveEnemy(WINDOW *win, int *ZyLoc, int *ZxLoc, int *yLoc, int *xLoc);



