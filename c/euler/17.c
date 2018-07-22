#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mytypes.h>

/* xmldoc
 * <problem>
 *      <description>
 *          If the numbers 1 to 5 are written out in words: one, two, three, four, five, 
 *          then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.
 *
 *          If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, 
 *          how many letters would be used?
 *
 *          NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) 
 *          contains 23 letters and 115 (one hundred and fifteen) contains 20 letters. 
 *          The use of "and" when writing out numbers is in compliance with British usage.
 *      </description>
 * </problem>
 */

u8 *ones[]   = { "zero", "one", "two", "three", "four", "five", "six", "seven",
                 "eight", "nine" };
u8 *ten[]    = { "ten", "eleven", "twelve", "thirteen", "fourteen", "fiveteen",
                 "sixteen", "seventeen", "eighteen", "nineteen" };
u8 *tenths[] = { "none", "ten", "twenty", "thirty", "fourty", "fifty", "sixty",
                 "seventy", "eighty", "ninety" };
u8 hundred[] = "hundred";

int main(void)
{
    u32 i;
    u32 sum_ones = 0;
    u32 sum_tenths = 0;
    u32 sum = 0;

    for( i=1; i < 10; i++ ) {
        sum += strlen( ones[i] );
    }
    sum_ones += sum;
    for( i=0; i < 10; i++ ) {
        sum += strlen( ten[i] );
    }
    for( i=20; i < 100; i+=10 ) {
        sum += strlen( tenths[i/10] ) + sum_ones;
    }
    sum_tenths = sum;
    for( i=100; i < 1000; i++ ) {
        sum += strlen( ones[i/100] ) + strlen( hundred ) + sum_tenths + (99*3);
    }
    printf("Number of letters from 1 - 1000 is %u \n", sum);
    return 0;
}
