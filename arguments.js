function foo(a) {
    arguments;          // list of arguments passed to foo.
    arguments[0] = 2;   // change value of first positional argument to 2.
    a;                  // is 2
    a = 4;
    arguments[0];       // is 4

    arguments.callee;           // function: foo
    arguments.callee.caller;    // function: bar
}
function bar() { foo(10); }
bar();
