#include <stdio.h>

int main(void)
{
    long long a = 0;
    long long b = 1, c;
    int i = 1000000 ;
    do {
        c = a + b;
        a = b;
        b = c;
    } while (i--);
    printf("%ld \n", b);
}
