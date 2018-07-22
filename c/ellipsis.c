#include <stdio.h>
#include <stdarg.h>

void func(char *format, ...);

void func(char *format, ...)
{
    va_list ap;
    int a;

    va_start(ap, format);
    vprintf(format, ap);
    /*
    printf("1. %x \n", ap);
    printf("2. %c \n", *ap);
    va_arg(ap, int);
    printf("3. %x \n", ap);
    */
}

int main(void)
{
    char str[] = "Hello world \n";
    func("%s %x %x \n", str, 10, 20);
}
