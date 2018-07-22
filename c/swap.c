#include <stdio.h>

#define SWAP(a,b) ( (a) = (a) ^ (b), (b) = (b) ^ (a), (a) = (b) ^ (a))

int temp = *a;
*a = *b;
*b = temp;

int main(void)
{
    int a = 10, b = 20;

    SWAP(a,b);
    printf("%d %d \n", a,b);
}
