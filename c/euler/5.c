#include <stdio.h>
#include <stdlib.h>
#include <mytypes.h>
#include <prime.h>

/* xmldoc
 * <problem>
 *     <description>
 *          2520 is the smallest number that can be divided by each of the
 *          numbers from 1 to 10 without any remainder.
 *
 *          What is the smallest number that is evenly divisible by all of the
 *          numbers from 1 to 20?
 *     </description>
 * </problem>
 */

s32 compareint( const void *a, const void *b )
{
    return *(u32_p)a - *(u32_p)b;
}

u64 lcm( u32_p numbers, u32 count )
{
    u32_p primes;
    u32 upto;
    u32 pcount;
    u32 i, j;
    u32 lcm = 1;

    qsort( numbers, count, sizeof(u32), compareint );

    for( i = 0; i < count; i++ ) {
        for( j = i+1; j < count; j++ ) {
            if((numbers[j] % numbers[i]) == 0) {
                numbers[j] /= numbers[i];
            }
        }
    }
    for( i = 0; i < count; i++ ) {
        lcm *= numbers[i];
    }
    return lcm;
}

int main(void)
{
    u32 numbers[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    printf("lcm = %u\n", lcm(numbers, 20));
}
