"8"==8, "8"===8, x==="8",   // => true, false, true
"8"!=5, "8"!==8, "8"!=="8", // => true, true, false
"8" > 5,                    // => true
"8" < 10,                   // => true
"8" >= 8,                   // => true
"8" <= 8,                   // => true
"a" < "b"                   // => true

// === is the preferred way to compare because,

""           ==   "0"       // => false
0            ==   ""        // => true
0            ==   "0"       // => true
false        ==   "false"   // => false
false        ==   "0"       // => true
false        ==   undefined // => false
false        ==   null      // => false
null         ==   undefined // => true
" \t\r\n"    ==   0         // => true

