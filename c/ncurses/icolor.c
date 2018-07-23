#include <ncurses.h>

int main(void) {
    initscr();
    start_color();
    if( !can_change_color() )
        addstr("This probably won’t work, but anyway:\n");
    init_color(1, 31, 31, 31);
    init_color(2, 31, 31, 31);
    init_pair(1,1,COLOR_BLACK);
    init_pair(2,2,COLOR_BLACK);
    attrset(COLOR_PAIR(1));
    printw("This is the new color %d.\n", 1);
    attrset(COLOR_PAIR(2));
    printw("This is the another color %d.\n", 2);
    refresh();
    getch();
    endwin();
    return 0;
}
