#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mytypes.h>
#include <palindrome.h>

/* xmldoc 
 * <description>
 *      Palindromes are of the form,
 *          'malayalam' or '121' or '101' etc ...
 *      This library provides helper functions to work with palindrom strings.
 *      Remember that even integers (in a given base) are treated as strings
 * </description>
 * <insight>
 *      Not all palindrom numbers are divisible by 11. But all numbers
 *      divisible by 11 are palindromes.
 * </insight>
 * <insight>
 *      All palindrom numbers (of base 10) that are even digit are divisible
 *      by 11.
 * </insight>
 */

u8 palindrome_file[] = "palindrome.bin";
u8_p palindromes[1000000];
u32 palcount = 0;

static void _storepalindrome( u8_p pstr );
static void _populate( u8_p pstr, u8_p pstr1, u8_p pstr2, const u8_p set, u8 recurse );

/* xmldoc
 * <function>_storepalindrome</function>
 * <parameter>
 *      char * pstr
 *      A palindrome string that needs to be stored into the global array,
 *          'palindromes'
 * </parameter>
 */

static void _storepalindrome( u8_p pstr )
{
    palindromes[palcount] = malloc( strlen(pstr) );
    strcpy( palindromes[palcount], pstr );
    palcount++;
}

/* xmldoc
 * <function>_populate</function>
 * <description>
 *      This is a recursive function which will populate the string with all
 *      possible combination of elements from 'set' to form a palindrome
 *      string. Once a valid palindrome string is formed, it will stored in a
 *      global array and return back, to start with the next combination.
 * </description>
 * <parameter>
 *      char * pstr
 *      The string starting address which will be populated with a palindrome.
 * </parameter>
 * <parameter>
 *      char * pstr1
 *      Pointer to the recursive function which will get incremented every call.
 * </parameter>
 * <parameter>
 *      char * pstr2
 *      Pointer to the recursive function which will get decremented every call.
 * </parameter>
 * <parameter>
 *      char * set
 *      The set of elements to be used to form a palindrom string, for numbers
 *      the set should contain char from '0' to '9', NULL terminated
 * </parameter>
 * <parameter>
 *      char recurse
 *      A count to maintain the number of recursive calls to make.
 * </parameter>
 */

static void _populate( u8_p pstr, u8_p pstr1, u8_p pstr2, const u8_p set, u8 recurse )
{
    const u8_p localset = set;
    u32 i;

    recurse--;
    for( i = 0; localset[i]; i++ ) {
        *pstr1 = localset[i];
        *pstr2 = localset[i];
        if( recurse ) {
            _populate( pstr, pstr1 + 1, pstr2 - 1, set, recurse );
        } else {
            if( pstr[0] != '0' ) {
                _storepalindrome( pstr );
            }
        }
    }
}

/* xmldoc
 * <function>ispalindrome</function>
 * <parameter>
 *      char * str
 *      String to be check for palindrome property
 * </parameter>
 * <return>
 *      1 - If 'str' is a palindrome
 *      0 - Otherwise
 * </return>     
 */

u32 ispalindrome( u8_p str )
{
    u32 len = strlen( (const u8_p) str );
    u32 i, j;
    for( i = 0, j = len-1; i < j ; i++, j-- ) {
        if( str[i] != str[j] ) {
            return 0;
        }
    }
    return 1;
}

/* xmldoc
 * <function>genpalindromes</function>
 * <parameter>
 *      char *set
 *      The set of elements to be used to form a palindrom string, for numbers
 *      the set should contain char from '0' to '9', NULL terminated
 * </parameter>
 * <parameter>
 *      char *minlen
 *      Minimum length of the palindrome string
 * </parameter>
 * <parameter>
 *      char *maxlen
 *      Maximum length of the palindrome string
 * </parameter>
 * <return>None</return>     
 */

u32 genpalindromes( const u8_p set, u8 minlen, u8 maxlen )
{
    FILE *fp = fopen( palindrome_file, "w" );
    u8 palin[256];
    u32 plen;
    u32 i;
    u64 val;

    for( plen = minlen; plen <= maxlen; plen++ ) {
        palin[plen] = 0;
        _populate( palin, palin, palin + plen -1, set,
                   plen & 1 ? (plen+1) / 2 : plen / 2 );
    }
    for( i = 0; i < palcount; i++ ) {
        val = (u64)atoll( palindromes[i] );
        if( val <= 0xFFFFFFFF ) {
            fwrite( &val, 4, 1, fp );
        }
    }
    fclose(fp);

    return palcount;
}

/* xmldoc
 * <function>getpalindromes</function>
 * <parameter>
 *      unsigned int *palindromes
 *      Caller allocated array into which the all the palindrome numbers read
 *      from the file are populated.
 * </parameter>
 * <return>
 *      int count
 *      Number of palindrome numbers read from the file.
 * </return>     
 */

u32 getpalindromes( u32_p palindromes )
{
    FILE *fp = fopen( palindrome_file, "r" );
    u32 count = 0;

    while( !feof( fp ) ) {
        count += fread( palindromes, 1, 1024, fp );
    }
    if( count % sizeof(*palindromes) ) {
        printf("Error : Stray bytes detected in the %s \n", palindrome_file );
        return 0;
    }
    return count / sizeof(*palindromes);
}
