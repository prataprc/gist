#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

int main( void )
{
    char            *dirname;
    char            *name;
    struct dirent   *dent;
    DIR             *dirfd;

    name    = "PWD";
    dirname   = getenv(name);
    if ( dirname ) {
        printf( "%s %s \n", name, dirname );
    } 
    else {
        printf( "%s not found \n", name );
    } 

    /* List the directory */
    dirfd   = opendir( dirname );
    if ( dirfd ) {
        while ( ( dent = readdir( dirfd ))) {
            printf(" %s \n", dent->d_name );
        }
    } else {
        printf( "Error : Opening directory %s \n", dirname );
    }
}

