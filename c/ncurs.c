#include <stdlib.h>
#include <stdio.h>
#include "ncurses.h"

#define NCURSES_ATTR_SHIFT       8
#define NCURSES_BITS(mask,shift) ((mask) << ((shift) + NCURSES_ATTR_SHIFT))

#define A_NORMAL	(1UL - 1UL)
#define A_ATTRIBUTES	NCURSES_BITS(~(1UL - 1UL),0)
#define A_CHARTEXT	(NCURSES_BITS(1UL,0) - 1UL)
#define A_COLOR		NCURSES_BITS(((1UL) << 8) - 1UL,0)

void main(void) {
    cchar_t a;
    printf("%d \n", sizeof(A_ATTRIBUTES));
    printf("%lx \n", A_ATTRIBUTES);
    printf("%lx \n", A_CHARTEXT);
    printf("%lx \n", A_COLOR);
    printf("%d \n", sizeof(a.chars));
}
