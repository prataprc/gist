#include <stdio.h>
#include <math.h>

long double mysqrt( long double n )
{
    return sqrtl(n);
}

int main( int argc, char *argv[] )
{
    long double n;
    long long limit = 1;
    long long i;
    long double res;
    if( argc > 1 ) {
        n = atoll(argv[1]);
    }
    if( argc > 2 ) {
        limit = atoll(argv[2]);
    }
    printf("n = %Lf ; limit = %lld \n", n, limit);
    for(i = 0; i < limit; i++ ) {
        res = mysqrt(n);
    }
    printf("%Lf\n", res);
}
