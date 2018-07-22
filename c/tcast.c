#include <stdio.h>
float foo(int a)
{
    return (float)a * a;
}

int main(void)
{
    char b;
    b = foo(10);
    printf("%d \n", b);
}
