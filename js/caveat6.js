var a = 1;      // global variable:
function f() {} // normal function:

delete a;   // false
delete f;   // false

// explicitly set property:
var obj = {x: 1}, arr = [0,1];
delete obj.x;   // true
delete arr[0];  // true
console.log(obj)
console.log(arr)

// a work around.
var GLOBAL_OBJECT = this;
GLOBAL_OBJECT.a = 1;
a === GLOBAL_OBJECT.a;  // true - just a global var
delete GLOBAL_OBJECT.a; // true
GLOBAL_OBJECT.a;        // undefined
