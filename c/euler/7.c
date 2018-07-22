#include <stdio.h>
#include <stdlib.h>
#include <mytypes.h>
#include <prime.h>

/* xmldoc
 * <problem>
 *     <description>
 *          What is the 10001st prime number?
 *     </description>
 * </problem>
 */

int main( void ) 
{
    u32 primes[10001*20];

    printf("Prime Numbers loaded %u \n", loadprimes( 10001 * 20 ), 10001 * 20);
    printf("There are %u primenumbers from 1-%u \n", getprimes( primes, 10001 * 20 ), 10001*20);
    printf("10001st prime number : %u\n", primes[10000] );
}
