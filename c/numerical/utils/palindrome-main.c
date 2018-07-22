#include <stdio.h>
#include <stdlib.h>
#include <mytypes.h>
#include <palindrome.h>

const char set[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\0' };

int main(void)
{
    u32 palcount;
    u64 val;
    palcount = genpalindromes( set, 1, 10 );
    printf("Number of palindromes %u \n", palcount);
    return 0;
}
