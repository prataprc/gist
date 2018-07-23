#include <ncurses.h>

int main(void) {
    int rows,cols, row,col;

    initscr();

    getmaxyx(stdscr,rows,cols);
    printw("Window size is %d rows, %d columns.\n",rows,cols);
    printw("Window size for standard screen is %d rows, %d columns.\n", 
           LINES, COLS);
    refresh();

    rows--; cols--;         // because top-left corner starts at 0,0
    mvaddch(0,0, '*');      // UL corner
    refresh();
    napms(500);             // pause half a sec.
    mvaddch(0,cols, '*');   // UR corner
    refresh();
    napms(500);
    mvaddch(rows,0, '*');   // LL corner
    refresh();
    napms(500);
    mvaddch(rows,cols, '*');    // LL corner
    refresh();
    napms(500);

    getyx(stdscr,row,col);
    mvprintw(4, 0,"\n\nThe cursor was at row %d, column %d\n",row,col);
    printw("when you stopped typing.");
    refresh();

    getch();
    endwin();
    return 0;
}
