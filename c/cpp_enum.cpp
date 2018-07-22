#include <stdio.h>

enum a_t {
    HELLO,
    WORLD,
};

a_t a = WORLD;

int main(void)
{
    printf("Hello World \n");
    printf("%s \n", (char *)a);
}
