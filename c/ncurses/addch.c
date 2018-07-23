#include <ncurses.h>

int main(void)
{
    char Ham1[] = "To be, or not to be: that is the question:\n";
    char Ham2[] = "Whether `tis nobler in the mind to suffer\n";
    char Ham3[] = "The slings and arrows of outrageous fortune,\n";
    char Ham4[] = "Or to take arms against a sea of troubles,\n";
    char Ham5[] = "And by end them?\n";
    char Ham5w[] = "opposing ";
    int  i;

    initscr();  /* Initialize ncurses */
    addstr(Ham1);
    addstr(Ham3);
    addstr(Ham5);
    refresh();
    getch();

    move(1, 0);         /* insert a blank line, scroll text down */
    // The insertln() function does not move the cursor;
    // it uses the cursor’s row position as a guide for which line to blank.
    insertln();
    refresh(); getch();
    addstr(Ham2);       /* line to insert */
    refresh(); getch(); /* wait for key press */

    move(3, 0);         /* insert a blank line, scroll text down */
    insertln();
    addstr(Ham4);       /* line to insert */
    refresh(); getch(); /* wait for key press */

    move(4,7); 
    i = 0;
    while(Ham5w[i]){ insch(Ham5w[i++]); refresh(); napms(500); }
    getch(); /* wait for key press */

    move(1,0); /* move to the line to delete */
    deleteln(); /* Delete and backscroll */
    refresh();
    getch(); /* wait for key press */

    move(3,7); 
    i = 0;
    while(Ham5w[i]){ delch(); refresh(); napms(500); i++; }
    getch(); /* wait for key press */

    endwin();   /* Restore, restore is automatic because of terminfo's rmcup */
    return 0;
}

