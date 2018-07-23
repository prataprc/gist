#include <ncurses.h>

#define INTERM "/dev/pts/3"
#define OUTTERM "/dev/pts/4"

int main(void) {
    FILE *termin, *termout;
    SCREEN *tp1, *tp2;
    char name[81];

    /* Open terminal one for reading Open terminal two for writing */
    termin = fopen(INTERM,"r");
    termout = fopen(OUTTERM,"w");
    if( termin==NULL || termout==NULL ) {
        puts("Unable to open terminal.");
        return(1);
    }

    /* set up the new terminal in NCurses */
    tp2 = newterm( NULL, termout, termin );
    if( tp2 == NULL ) {
        puts("Unable to open terminal window.");
        return(2);
    }

    /* NCurses is now started for the new terminal */
    tp1 = set_term(tp2);    /* This is equivalent of initscr() */
    printw("Welcome to NCurses output on terminal %s.\n",OUTTERM);
    printw("You can type on terminal %s, and see it ; here.\n",INTERM);
    addstr("What is your name: ");
    refresh();
    getnstr(name,80);
    printw("%s, glad to have you aboard!",name);
    getch();

    // Many terminals, such as xterm, support a feature known as rmcup. It
    // restores the screen to what it looked like before a program was run.
    // The situation also occurs with any full-screen terminal program, such as
    // man or less; the program's text disappears after you quit the program,
    // and the prompt “window” is restored.  
    endwin();
    return 0;
}

