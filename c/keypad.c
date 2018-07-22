#include <ctype.h>

int main(void)
{
    int c = 269;

    if ( isalnum(c) ) {
        printf("isalnum");
    }
    if (c == ' ') {
        printf(" ");
    }
    if (c == '_') {
        printf("_");
    }
    if (c == '.') {
        printf(".");
    }
    if (c == '/') {
        printf("/");
    }
    printf("\n");
}
