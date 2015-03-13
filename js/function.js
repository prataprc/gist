foo();  // Works because foo was created before this code runs
function foo() {}

bar();  // Fails : TypeError
var bar = function() { console.log('anonymous'); };

var mat = function bar( bool ) {
    if( bool ) {
        console.log('recurse');
        // Refers to itself, name of the function is made available in the
        // local-scope.
        bar(false);
    } else {
        console.log('recursion done');
    }
}
bar();              // Refers to anonymous function
mat(true);
