#include <stdio.h>

void swap( char * src, char *dest )
{
    char t;
    while ( src != dest ) {
        t       = *src;
        *src    = *dest;
        *dest   = t;
        src++;
        dest--;
    }
}

int line_reverse( char * str )
{
    char *src  = NULL;

    while ( *str ) {
        if ( src == NULL && *str != ' ' ) {
            src = str;
        } else if ( src && *str == ' ' ) {
            swap( src, str-1 );
            src = NULL;
        }
        str++;
    }
    if ( src ) {
        swap( src, str-1 );
    }
}

int main( void )
{
    char a[] = "hello";
    char b[] = "hello world";
    char c[] = " hello world";
    char d[] = " hello world ";
    line_reverse( a );
    line_reverse( b );
    line_reverse( c );
    line_reverse( d );
    printf("%s \n", a);
    printf("%s \n", b);
    printf("%s \n", c);
    printf("%s \n", d);
}
