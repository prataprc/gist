#include <stdio.h>

#define MAX(a,b) (a) > (b) ? (a) : (b)

int factorial(int);

static inline int MAX_fn(int a, int b)
{
    return a > b ? a : b;
}

int main(void)
{
    int a, fact;
    scanf("%d", &a);

    fact = factorial(a);
    printf("%d \n", MAX_fn(a,fact));
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
           
