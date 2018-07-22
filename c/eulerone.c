#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] ) {
    unsigned int i;
    unsigned long long sum = 0;
    for( i=1 ; i<= 3333333; i++ ) {
        sum += (i*3) < 10000000 ? i*3 : 0;
        sum += (i*5) < 10000000 ? i*5 : 0;
    }
    for( i=1 ; i<66667; i++ ) {
        sum -= (i*15) < 10000000 ? i*15 : 0;
    }
    printf("%llu\n", sum);
}
