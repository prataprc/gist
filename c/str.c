#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int     main(void)
{
    int a = 10;
    int i;
    char buffer [33];

    printf("int : %d string : %s \n", a, a );

    printf ("Enter a number: ");
    scanf ("%d",&i);
    itoa (i,buffer,10);
    printf ("decimal: %s\n",buffer);
    itoa (i,buffer,16);
    printf ("hexadecimal: %s\n",buffer);
    itoa (i,buffer,2);
    printf ("binary: %s\n",buffer);
    return 0;
}

