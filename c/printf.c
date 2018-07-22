#include <stdio.h>

int main(void)
{
    printf("%c",0);
    printf("%02x %04x %08x \n", 0x12345678,  0x12345678,  0x12345678);
    printf("%d \n", printf("hello world\n"));
}
