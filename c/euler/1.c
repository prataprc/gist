#include <stdio.h>
#include <stdlib.h>
#include <mytypes.h>

/* xmldoc
 * <problem>
 *     <description>
 *         If we list all the natural numbers below 10 that are multiples of 3 or
 *         5, we get 3, 5, 6 and 9. The sum of these multiples is 23.
 *         Find the sum of all the multiples of 3 or 5 below 1000.
 *     </description>
 * </problem>
 */

u64 sum( u32_p integers, u32 count )
{
    u64 s = 0;
    while( count ) {
        s += integers[count-1];
        count--;
    }
    return s;
}

s32 compareint( const void *a, const void *b )
{
    return *(u32_p)a - *(u32_p)b;
}

u64 sumfactors( u32 n, u32_p factors, u32 count )
{
    u32 i, j, k;
    u32 m;
    u64 sum = 0;
    u32 skip = 0;

    qsort(factors, count, sizeof(u32), compareint);

    for( i = 0 ; i < count; i++ ) {
        if( factors[i] == 0 ) {
            continue;
        }
        for( j = i+1; j < count; j++ ) {
            if( factors[j] == 0 ) {
                continue;
            }
            if( (factors[j] % factors[i]) == 0 ) {
                factors[j] = 0;
            }
        }
    }
    for(i = 0; i < count; i++) {
        if (factors[i] == 0) {
            continue;
        }
        m = factors[i];
        while( m < n ) {
            for( k = i+1; k < count; k++ ) {
                if( factors[k] && (m % factors[k]) == 0 ) {
                    skip = 1;
                    break;
                }
            }
            if( skip ) {
                skip = 0;
            } else {
                sum += m;
            }
            m += factors[i];
        }
    }
    return sum;
}

#if 1
s32 main(void)
{
    u32 factors[] = {3, 5};
    printf("%ld \n", sumfactors( 1000, factors, 2 ));
}
#else
/* This alternate algorithm is to mimick the python implementation. And the
 * measurement says that it is just 3 times faster than the python
 * implmentation
 */
u32 factors[] = {3, 5, 10, 2};
u32 multiples[1000000];
int main(void)
{
    u32 i, j, skip = 0;
    u32 m;
    u32 moff = 0;
    u64 sum = 0;

    for( i = 0; i < 4; i++ ) {
        for( m = factors[i]; m < 10000; m += factors[i] ) {
            for( j = 0; multiples[j]; j++ ) {
                if( m == multiples[j] ) {
                    skip = 1;
                    break;
                }
            }
            if( skip ) {
                skip = 0;
                continue;
            } else {
                multiples[moff] = m;
                moff++;
            }
        }
    }
    for( i = 0; i < moff; i++ ) {
        sum += multiples[i];
    }
    printf("%ld\n", sum);
}
#endif
