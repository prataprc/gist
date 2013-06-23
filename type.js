// The following is a table of values - its class and type.
console.log([
    "foo",               // String     string
    new String("foo"),   // String     object
    1.2,                 // Number     number
    new Number(1.2),     // Number     object
    true,                // Boolean    boolean
    new Boolean(true),   // Boolean    object
    new Date(),          // Date       object
    new Error(),         // Error      object
    [1,2,3],             // Array      object
    new Array(1, 2, 3),  // Array      object
    new Function(""),    // Function   function
    /abc/g,              // RegExp     object (function in Nitro/V8)
    new RegExp("meow"),  // RegExp     object (function in Nitro/V8)
    {},                  // Object     object
    new Object(),        // Object     object
])

typeof(10)                    // To retrieve the type of an object
Object.prototype.toString(10) // To retrieve the class of an object

var n = Number(10)      // is same as literal 10,
var m = new Number(10)  // is literal 10 wrapped inside an object.
n == m      // => true
n === m     // => false
