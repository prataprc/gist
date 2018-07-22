#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char a[] = "hello       world";
    char b[] = "prana";
    FILE *fp;
    fp = fopen( "data.txt", "r+" );
    fwrite( a, 1, strlen(a), fp );
    fclose(fp);
    getchar();
    fp = fopen( "data.txt", "r+" );
    fseek( fp, 6, SEEK_SET );
    fwrite( b, 1, strlen(b), fp );
    fclose(fp);
}
