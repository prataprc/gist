#include <stdio.h>

int main(void)
{
    char str[] = "1024,0x2048";
    char *p = str;
    int i;

    printf("#### strtol ####\n");
    i = strtol(p, NULL, 0);
    printf("%d \n", i);
    i = strtol(p+5, NULL, 0);
    printf("%x \n", i);
    i = strtol(p+7, NULL, 0);
    printf("%x \n", i);
    printf("#### strtoull ####\n");
    printf("%lx \n", strtoull("0x10", NULL, 16));
    printf("%lx \n", strtoull("0x1000", NULL, 16));
    printf("%lx \n", strtoull("10002000", NULL, 10));
    printf("%lx \n", strtoull("1000200030004000", NULL, 10));
}
