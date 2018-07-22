#include <stdio.h>
#include <stdlib.h>
#include <mytypes.h>
#include <prime.h>

/* xmldoc
 * <problem>
 *     <description>
 *          Find the sum of all the primes below two million.
 *     </description>
 * </problem>
 */

int main( void ) 
{
    u32 primes[2000000/10];
    u32 i;
    u64 sum = 0;

    printf("Prime Numbers loaded %u \n", loadprimes( 2000000 ));
    printf("There are %u primenumbers from 1-%u \n", 
            getprimes( primes, 2000000 ), 2000000);
    for( i = 0; primes[i] < 2000000; i++ ) {
        sum += primes[i];
    }
    printf("Sum of primes numbers less than 2000000 is %llu \n", sum );
}
