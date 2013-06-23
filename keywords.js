var a;                      // variable declaration - global
var a=[true, false];        // boolean keywords
var a=[Infinity, NaN];      // numeric
var a=[null, undefined];    // object
fn = function hw() {}       // function definition
Number(10);                 // keyword that bakes numeric data-type
String('10');               //  that bakes string data-type
Boolean(true);              //  that bakes boolean data-type
Function('console.log(10)') //  that bakes function data-type
Array(10, 20);              //  that bakes array-like object data-type
RegExp(10);                 //  that bakes regexp-like object data-type
Date();                     //  that bakes date like object data-type

typeof(a);                  // return a string denoting typeof a

obj = { 'first-name': 'arun', 'age': 22 };
delete obj['first-name']    // delete the key `first-name` from obj

return;     // return value from function, otherwise function implicitly
            // returns `undefined`.
