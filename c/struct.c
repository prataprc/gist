#include <stdio.h>

struct a {
    int a;
    int b;
    char str[10];
    int c;
};
typedef struct a *a_p;

struct a element = {
    10,
    20,
    {},
    30
};

struct w {
    int a;
};

int main(void)
{
    a_p e = &element;
    printf("%d %d %d \n", element.a, element.b, element.c);
    printf("%d %d \n", sizeof(a_p), e->a);
    func_a();
    return 0;
}

int func_a(void)
{
    struct a aa;
    struct a bb;
    aa.a = 10;
    bb = aa;
    printf("aa @ %x, bb @ %x\n", &aa, &bb);
    printf("%d %d\n", aa.a, bb.a);
}

int func_w(void)
{
    struct w ww;
    ww.a = 10;
    printf("%d \n", ww.a);
}
