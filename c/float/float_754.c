#include <stdio.h>

int main(void)
{
    float ft;
    unsigned int *fi;

    for (ft = 0; ft < 1; ft += 0.000001) {
        fi = (unsigned int *) &ft;
        printf("s = %d e = %d m = %d \n", *fi & 0x80000000, 
                (*fi >> 23) & 0xFFFF, *fi & 0x7FFFFF);
    }
}
