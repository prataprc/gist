foo();              // Works because foo was created before this code runs
function foo() {}

foo;    // 'undefined'
foo();  // this raises a TypeError
var foo = function() {};
