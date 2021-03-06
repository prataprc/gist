#include <stdio.h>
#include <stdlib.h>

/* xmldoc
 *
 * <problem>
 *     <description>
 *          A palindromic number reads the same both ways. The largest palindrome
 *          made from the product of two 2-digit numbers is 9009 = 91 × 99.
 *          Find the largest palindrome made from the product of two 3-digit
 *          numbers.
 *     </description>
 *     <solution>
 *          You can also do this with pen and paper. You have a number:
 *
 *          (100a + 10b + c)(100d + 10e + f)
 *
 *          Which is a palindrone. This factors out to:
 *
 *          100cd + 10ce + cf +
 *          1000bd + 100be + 10bf +
 *          10000ad + 1000ae + 100af
 *
 *          Assuming the first digit is 9, then cf must be equal to nine.
 *          Also, both a and d must then be equal to nine. The only ways
 *          to make the last digit of the product of two integers 9 would
 *          be if those integers were either of:
 *
 *          1 and 9
 *          3 and 3
 *          7 and 7
 *
 *          So, both numbers must start with 9, end with either 1, 3, 7,
 *          or 9, and one of them must be divisible by 11. The only
 *          numbers divisible by 11 from 900 - 1000 are:
 *
 *          902
 *          913
 *          924
 *          935
 *          946
 *          957
 *          968
 *          979
 *          990
 *
 *          You can discard all of those that do not end in either 1, 3,
 *          7, or 9, and you are left with:
 *
 *          913
 *          957
 *          979
 *
 *          So now the presumed answer is either:
 *
 *          (900 + 10 + 3)(900 + 10x + 3)
 *          (900 + 50 + 7)(900 + 10x + 7)
 *          (900 + 70 + 9)(900 + 10x + 1)
 *
 *          Factoring all those out, you get:
 *
 *          810000 + 9000x + 2700 + 9000 + 100x + 30 + 2700 + 30x + 9
 *          824439 + 9130x
 *
 *          Now, for the first digit 824439 + 9130x to be 9, x must be 9
 *          (if x were 8, then 824439 + 9130x = 897479, and the first
 *          digit is 8). And so you have 913 * 993, which is the answer.
 *          You can factor the others out to see if they produce a bigger
 *          answer, which they don't.
 *     </solution>
 * </problem>
 */

/* This problem is solved using ipython and few library interface */
