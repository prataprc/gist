#include <stdio.h>

int factorial(int);

int main(void)
{
    printf("%d \n", factorial(10));
}

int factorial(int num)
{
    static int fact;
    if (num) {
        fact = factorial(num - 1) * num;
        return fact;
    } else {
        fact = 1; 
        return 1;
    }
}
           
