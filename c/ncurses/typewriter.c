#include <ncurses.h>

int main(void) {
    char ch, i=0;
    char list[100];

    initscr();
    addstr("Type a few lines of text\n");
    addstr("Press ~ to quit\n");
    refresh();
    /* Note that pressing Enter will only do CR on the screen doesn't do a
     * combination of CR+LF - But works fine with addstr() */
    while( (ch = getch()) != '~') { list[i++] = ch; };
    list[i] = 0;
    addstr(list);
    getch();
    endwin();
    i = 0;
    while(list[i]) { printf("%x ", list[i++]); };
    printf("\n");
    return 0;
}
