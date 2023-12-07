#include <ncurses.h>
int splash_screen();
void display_level(WINDOW *win, int lvl);
//int *Enemies(WINDOW *win, int MAX_ENEMIES, int lvl, int *ZyLoc, int *ZxLoc);
//void printEnemies(WINDOW *win, int MAX_ENEMIES, int *ZyLoc, int *ZxLoc);
//int upgrade_box(WINDOW *win, int MAX_NUM, int *yLoc, int *xLoc);
void bullet(WINDOW *win, int *ZyLoc, int *ZxLoc, int *yLoc, int *xLoc, char *dir, int key);
void sleep_ms(int milliseconds);
void quit_screen();
