#include <stdio.h>

typedef union {
    struct {
        unsigned int a:16;
        unsigned int b:16;
    } x;
    unsigned int dword;
} bits_t;

int main( void )
{
    bits_t i;
    unsigned int j;

    i.x.a = 0x1234;
    i.x.b = 0x5678;
    printf("%x \n", i.dword); 
}

