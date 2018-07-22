#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <mytypes.h>
#include <prime.h>

int main(void)
{
    u32 fact[100];
    u32 fcount = 0;
    u32 i;

    printf("Number of Prime numbers %d \n", genprime(0xFFFFFFFF));
    factors( 29, fact, &fcount );
    printf("No of factors %u\n", fcount);
    for( i = 0; i < fcount ; i++ ) {
        printf("%u ", fact[i] );
    }
    printf("\n");
}
