#include <stdio.h>

int main(void)
{
    int a;
    char *s;

    a = 0x12345678;
    s = (char*)&a;

    printf("a: %x %p %x %x %x %x", a, &a, *(s+0), *(s+1), *(s+2), *(s+3));
}
