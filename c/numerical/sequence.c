#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mytypes.h>
#include <sequence.h>

/* Refer to link http://en.wikipedia.org/wiki/Square_pyramidal_number */

u64 sumofssquares( u32 upto )
{
    u64 n = upto;
    return ((2 * n * n * n) + (3 * n * n) + n ) / 6;
}

u64 sumofseq( u32 upto )
{
    u64 n = upto;
    return (((n * n) + n) / 2);
}

u32 rowintriangle( u32 index )
{
    f64 row;
    /*      n(n+1) / 2 = S
     * =>   n = (-1 + sqrt( 1 + 8S )) / 2
     */
    row = (-1 + sqrt((f64)(1 + 8 * index ))) / 2;
    row = ceil(row);
    return (u32) row;
}
