#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int j, i = 10,k ;
    // (i++)--;
    j = 1337;
    if (i==20) {
        printf("%d", i);
        exit(1);
    }
    while(1) {
        i = 0;
        while (j) {
            j *= 42;
            i++;
        }
        getchar();
        printf("%d\n", i);
    }
}
