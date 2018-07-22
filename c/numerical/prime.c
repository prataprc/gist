#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <mytypes.h>
#include <prime.h>

static u32 allprimes[256 * 1024 * 1024];
static u32 primecount = 0;
const u8 primefile[] = "prime.bin";

/* Parameter count should be initialised to ZERO */
void factors( u32 num, u32 *fact, u32 *count )
{
    u32 sroot = sqrtl( (f96) num ) + 1;
    u32 i;
    
    if( primecount == 0 ) {
        genprime( 0xFFFF );
    }
    for( i = 0 ; allprimes[i] <= sroot ; i++ ) {
        if ((num % allprimes[i]) == 0 ){
            *fact = allprimes[i];
            fact++;
            *count = *count + 1;
            factors( num / allprimes[i], fact, count );
            break;
        }
    }
    if( allprimes[i] > sroot && *count != 0 ) {
        *fact = num;
        *count = *count + 1;
    }
    return;
}

static u32 _isprime( u32 num, u32 *primes )
{
    u32 sroot = sqrtl( (long double)num ) + 1;
    u32 i;

    i = 0;
    for( i = 0; primes[i] < sroot; i++ ) {
        if( (num%primes[i]) == 0 ) {
            return 0;
        }
    }
    return 1;
}

u32 genprime( u32 limit )
{
    FILE *fp = fopen( primefile, "wb" );
    u32 i;
    u32 startnum = 2;
    u32 *resptr = allprimes;

    printf("Generating Prime numbers from 0 - %u \n", limit);
    primecount = 1;
    *resptr = 2;
    resptr++;
    for( i = 3 ; i < limit; i+=2 ) {
        if( _isprime(i, allprimes) ) {
            *resptr = i;
            resptr++;
            primecount = primecount + 1;
        }
    } 
    *resptr = 0;
    fwrite(allprimes, 4, primecount, fp);
    fclose(fp);
    return primecount;
}

/* 'upto' is not strict, sometimes slightly more number of primes numbers can
 * get loaded
 */
u32 loadprimes( u32 upto )
{
    FILE *fp = fopen( primefile, "rb" );
    u32 *ptr = allprimes;

    if( fp == NULL ) {
        perror("Unable to open prime nubmer file in 'rb' mode");
        return 0;
    }
    primecount = 0;
    if( fp ) {
        while( !feof(fp) ) {
            primecount += fread( ptr, 4, 256, fp );
            ptr = allprimes + primecount;
            if( allprimes[primecount-1] >= upto ) {
                break;
            }
        }
    }
    fclose(fp);
    return primecount;
}

u32 getprimes( u32 *primes, u32 upto )
{
    u32 count;
    for( count = 0; allprimes[count] <= upto; count++ ) {
        *primes = allprimes[count];
        primes++;
    }
    return count;
}

