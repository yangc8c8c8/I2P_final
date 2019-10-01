#include "font.h"
#ifndef FRAMEWORK_
#define FRAMEWORK_
#define NUM_KEYS3 4
struct t_menu {
    int x;
    int y;
    int fgcolor;
    int bgcolor;
    int cursor;
    int num_options;
    int state[15];
    char text[15][30]; /* 程﹃  –﹃程 79 じ */
    char alt_text[15][30]; /* 程﹃  –﹃程 79 じ */
    Font *large_font;
};
typedef struct
{
    int x;
    int y;
    int fgcolor;
    int bgcolor;
    int cursor;
    int num_options;
    int state[15];
    char text[15][30];
    char alt_text[15][30];
    Font *large_font;
}Pausescreen;
typedef struct t_menu Menu;


extern int IsOnItem(Menu *m, int index);
extern int IsItemSelected(Menu *m, int index);
extern void showMenu(Menu *m);
extern void scrollMenu(Menu *m, int diff);
extern void radioMenu(Menu *m);
extern void toggleMenu(Menu *m);
int pause(Pausescreen*);
void setpause(Pausescreen *p);
void showpause(Pausescreen *p);
int IsOnItemp(Pausescreen *p, int index);
int IsItemSelectedp(Pausescreen *p, int index);
void scrollpause(Pausescreen *p, int diff);
void radiopause(Pausescreen *p);
void togglepause(Pausescreen *p);

#endif

