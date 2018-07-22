#include <stdio.h>
#include <regex.h>

int main( void )
{
    char    patt[] = "errinject[^ ]*\\>";
    char    line[] = "errinject";
    int     i;
    regex_t preg;
    regmatch_t pmatch[10];

    printf( "%s \n", line );
    regcomp( &preg, patt, REG_EXTENDED | REG_NEWLINE );
    if ( 0 == regexec( &preg, line, 1, pmatch, 0 ) ) {
        for (i = 0; i < 10 ; i++ ) {
            printf( "%d %d, ", pmatch[i].rm_so, pmatch[i].rm_eo );
        }
        printf("\n");
    }
}
