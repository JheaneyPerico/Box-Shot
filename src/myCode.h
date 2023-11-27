#include <ncurses.h>
int splash_screen();
void display_level(WINDOW *win, int lvl);
void Enemies(WINDOW *win, int MAX_ENEMIES, int lvl, int *yLoc, int *xLoc);
int upgrade_box(WINDOW *win, int MAX_NUM);
void quit_screen();
