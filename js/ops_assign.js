var i = 2, j=7; // assignment is a side-effect operator
i++; i--;       // evaluates after use => 2
++i; --i;       // evaluates before use => 2

i += 2;     // 4
i -= 1;     // 3
i *= 2;     // 6
i /= 3;     // 2
i %= 2;     // 0

// assignments create side effects and also treated as expression,
(x=10) * 200    // => 2000
x+20            // => 30
function bar() { return [ a=10, b="hello" ]; }
[a, b, bar()]   // Error
[bar(), a, b]   // => [[10, "hello"], 10, "hello"]
