#include <stdio.h>
#include <stdlib.h>
#include <mytypes.h>
#include <prime.h>

/* xmldoc
 * <problem>
 *     <description>
 *         The prime factors of 13195 are 5, 7, 13 and 29.
 *         What is the largest prime factor of the number 600851475143 ?
 *     </description>
 * </problem>
 */

int main(void)
{
    u32 results[100];
    u32 count = 0;

    loadprimes( 13195 );
    factors( 13195, results, &count );
    printf("The factors are : \n\t");
    while( count-- ) {
        printf("%u ", results[count]);
    }
    printf("\n");
}
