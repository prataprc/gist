#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char x[100]="hello world";
    char y[100];
    char *src = x, *dst = y;
    
    while(*dst++ = *src++);
}
