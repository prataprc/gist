#include <curses.h>
 
int main () {
    int x, y, c=0;
    char s[10];

    // It’s important to remember that the COLORS value tells you how many 
    // colors are available, yet the colors are numbered starting with zero.
    // So the range of colors available is 0 through COLORS minus one.

    // A color pair is simply a combination of foreground and background color
    // attributes. Each combination is a color pair and assigned a number from
    // 1 through the value of COLOR_PAIRS minus 1.

    initscr ();
    start_color();
    printw("All of %d colors :\n", COLORS-1);
    for(x=0; x < COLORS-1; x++) {
        if((x % 16) == 0) addch('\n');
        init_pair(++c, x, 0);
        attrset(COLOR_PAIR(c));
        sprintf(s, "%4d", x);
        addstr(s);
    }
    printw("\n\n");

    refresh ();
    getch();

    clear();
    //init_pair(c, COLOR_WHITE, COLOR_YELLOW);
    //bkgd(COLOR_PAIR(c));
    attrset(COLOR_PAIR(100));
    printw("All of %d colors-pairs :\n", COLOR_PAIRS-1);
    c = 0;
    for (x = 0; x < COLORS-1; x++) {
        if((x % 16) == 0) addch('\n');
        init_pair (++c, 254, x);
        attrset(COLOR_PAIR(c));
        sprintf(s, "%4d", x);
        addstr(s);
    }
    refresh ();
    getch();

    endwin();
}
