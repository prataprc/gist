// Arithematic operators
3+2, 'explain'+'that',  // 5, explainthat
2-3,                    // -1
3*2,                    // 6
3/2,                    // 1.5
3%2,                    // 1

// Comparison operators
"8"==8, "8"===8, x==="8",   // => true, false, true
"8"!=5, "8"!==8, "8"!=="8", // => true, true, false
"8" > 5,                    // => true
"8" < 10,                   // => true
"8" >= 8,                   // => true
"8" <= 8,                   // => true
"a" < "b"                   // => true

// === is preferred way to compare

""           ==   "0"       // => false
0            ==   ""        // => true
0            ==   "0"       // => true
false        ==   "false"   // => false
false        ==   "0"       // => true
false        ==   undefined // => false
false        ==   null      // => false
null         ==   undefined // => true
" \t\r\n"    ==   0         // => true

// logical operators
true && false,      // => false
true || false,      // => true
!false              // => true

true ? 'it was true' : 'it was false',

var i = 2, j=7; // assignment side-effect operator
i++; i--;       // 2, evaluates after use
++i; --i;       // 2, evaluates before use

i += 2;     // 4
i -= 1;     // 3
i *= 2;     // 6
i /= 3;     // 2
i %= 2;     // 0

2&7,    // 010 & 111 => 010 (2)
2|7,    // 010 | 111 => 111 (7)
2^7,    // 010 & 111 => 101 (5)
2<<1,   // 10 << 1   => 100 (4)
-2<<1,  // -4
2>>1,   // 10 >> 1   => 001 (1)
-2>>1,  // -1   (arithmatic right shift)
2>>>1,  // 1
-2>>>1  // logical righ shift
        //    (-2) is  11111111111111111111111111111110
        // 2147483647, 01111111111111111111111111111111

// Note: There is no real way to compare equality of non-primitive objects.
// Because, object attribute can refer to function-methods that can't be
// compared.
