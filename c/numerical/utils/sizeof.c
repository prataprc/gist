#include <stdio.h>
#include <stdlib.h>
#include "include/mytypes.h"

int main( void )
{
    printf("Sizeof u8       : %d\n", sizeof(u8));
    printf("Sizeof u8_p     : %d\n", sizeof(u8_p));
    printf("Sizeof s8       : %d\n", sizeof(s8));
    printf("Sizeof s8_p     : %d\n", sizeof(s8_p));
    printf("Sizeof u16      : %d\n", sizeof(u16));
    printf("Sizeof u16_p    : %d\n", sizeof(u16_p));
    printf("Sizeof s16      : %d\n", sizeof(s16));
    printf("Sizeof s16_p    : %d\n", sizeof(s16_p));
    printf("Sizeof u32      : %d\n", sizeof(u32));
    printf("Sizeof u32_p    : %d\n", sizeof(u32_p));
    printf("Sizeof s32      : %d\n", sizeof(s32));
    printf("Sizeof s32_p    : %d\n", sizeof(s32_p));
    printf("Sizeof u64      : %d\n", sizeof(u64));
    printf("Sizeof u64_p    : %d\n", sizeof(u64_p));
    printf("Sizeof s64      : %d\n", sizeof(s64));
    printf("Sizeof s64_p    : %d\n", sizeof(s64_p));
    printf("Sizeof f32      : %d\n", sizeof(f32));
    printf("Sizeof f32_p    : %d\n", sizeof(f32_p));
    printf("Sizeof f64      : %d\n", sizeof(f64));
    printf("Sizeof f64_p    : %d\n", sizeof(f64_p));
    printf("Sizeof f80      : %d\n", sizeof(f80));
    printf("Sizeof f80_p    : %d\n", sizeof(f80_p));
}
