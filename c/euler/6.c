#include <stdio.h>
#include <stdlib.h>
#include <mytypes.h>
#include <sequence.h>

/* xmldoc
 * <problem>
 *     <description>
 *          Find the difference between the sum of the squares of the first
 *          one hundred natural numbers and the square of the sum.
 *     </description>
 * </problem>
 */

/* Important :
 *      The default size of argument passed through ellipsis declaration seems to
 *      be the default machine word size. So, a u64 number can be pushed as a u32
 *      number on a 32-bit machine
 */

int main( void ) 
{
    u64 s = sumofseq(100);
    s = s * s;
    printf("%u \n", sumofssquares(100));
}
