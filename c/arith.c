#include <stdio.h>

int main(void)
{
    int a, b, c;

    a = 7 / -3;
    b = -7 / 3;
    c = 7 / 3;

    printf("Div. 7/-3 = %d, -7/3 = %d, 7/3 = %d \n", a, b, c);

    a = 7 % -3;
    b = -7 % 3;
    c = 7 % 3;

    printf("Div. 7%-3 = %d, -7%3 = %d, 7%3 = %d \n", a, b, c);
}
