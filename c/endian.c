#include <stdio.h>
#include <stdarg.h>

int main(void)
{
    unsigned int mem;
    unsigned int *ptr = &mem;
    unsigned short *ptrw = &mem;
    unsigned char *ptrb = &mem;

    *ptr = 0x12345678;
    printf("%x \n", mem);
    *(ptrw) = 0x5678; *(ptrw + 1) = 0x1234;
    printf("%x \n", mem);
    *(ptrb) = 0x78; *(ptrb + 1) = 0x56; *(ptrb + 2) = 0x34; *(ptrb + 3) = 0x12;
    printf("%x \n", mem);
}
