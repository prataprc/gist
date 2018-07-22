#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mytypes.h>

/* xmldoc
 * <problem>
 *      <description>
 *          The following iterative sequence is defined for the set of positive
 *          integers:
 *              n → n/2 (n is even)
 *              n → 3n + 1 (n is odd)
 *          Using the rule above and starting with 13, we generate the 
 *          following sequence:
 *              13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
 *          It can be seen that this sequence (starting at 13 and finishing at 1)
 *          contains 10 terms. Although it has not been proved yet 
 *          (Collatz Problem), it is thought that all starting numbers finish 
 *          at 1.
 *          Which starting number, under one million, produces the longest chain?
 *
 *          NOTE: Once the chain starts the terms are allowed to go above one million.
 *      </description>
 * </problem>
 */

#define MAXCHAIN 1000000

u32 collatzchain( u32 num, u32 *chain, u32 index )
{
    chain[index] = num;
    if( num & 1 ) {     /* Odd */
        num = 3 * num + 1;
    } else {            /* Even */
        num = num >> 1;
    }
    if( num == 1 ) {
        chain[index] = num;
        return index + 1;
    } else if( index >= 1000000 ) {
        return 0;
    } else {
        return collatzchain( num, chain, index + 1 );
    }
}

int main( void ) 
{
    u32 chain[MAXCHAIN];
    u32 i;
    u32 num;
    u32 count;
    u32 max = 0;

    for( num = 1; num < 1000000; num++ ) {
        count = collatzchain( num, chain, 0 );
        if( count ) {
            max = count > max ? count : max;
        } else {
            printf("The Collatz chain for the number %u seems to exceed %u steps \n", 
                    num, MAXCHAIN );
        }
    }
    printf("Maximum steps in the Collatz Chain is %u \n", max);
}
