#include <stdio.h>

class ac {
    public :
    static int a[2][2];
};

int ac::a[2][2] = { {1,2}, {1} };
int main(void)
{
    int b[2][2] = { {3,4}, {2} };
    ac::a = b;
    ac obj;
}
