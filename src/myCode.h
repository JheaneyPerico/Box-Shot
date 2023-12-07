#include <ncurses.h>
int splash_screen();
void display_level(WINDOW *win, int lvl);
void bullet(WINDOW *win, int *ZyLoc, int *ZxLoc, int *yLoc, int *xLoc, char *dir, int key);
void sleep_ms(int milliseconds);
void quit_screen();
