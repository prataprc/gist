#include <stdio.h>
#include <ctype.h>

char str[]  = "HELLO WORLD";

int main( void )
{
    char *ptr = str;

    while (*ptr) {
        *ptr = tolower(*ptr); ptr++; 
    }
    printf( "%s %s \n", str, ptr );
}
