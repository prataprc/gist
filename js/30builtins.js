// Basic types using literals and tokens.
console.log( '10 is ' + typeof(10) )    // => number
console.log( '1000000000000 is ' + typeof(1000000000000) ) // => number
console.log( '10.0 is ' + typeof(10.0) )                   // => number
console.log( '"hello" is ' + typeof('hello') )             // => string
console.log( '{} is ' + typeof({}))                        // => object
console.log( '[] is ' + typeof([]))                        // => object
console.log( '// is ' + typeof(/ab.xz/))                   // => object
console.log( 'function(){} is ' + typeof(function(){}) )   // => function
console.log( 'Object() is ' + typeof(Object()) )           // => object

console.log('\ntypeof returns ' + typeof(typeof(function(){})) ) // => string

console.log("\nbuilt-in types:");
console.log(Number);            // => [Function: Number]
console.log(Number(10));        // => 10
console.log(Boolean);           // => [Function: Boolean]
console.log(Boolean(true));     // => true
console.log(String);            // => [Function: String]
console.log(String('hello'));   // => 'hello'
console.log(Date);              // => [Function: Date]
console.log(Date(100));         // => <current-date>, arguments are useless
console.log(Array);                      // => [Function: Array]
console.log([Array([1,2]), Array(1,2)]); // => [ [ 1, 2 ] ], [ 1, 2 ] ]

console.log([RegExp, RegExp('ab.xy'), RegExp(/ab.xy/)]);
                                // => [Function: RegExp], /ab.xy/, /ab.xy/]
console.log(Object, Object(10)]);
                                // => [ [Function: Object], {} ]
console.log(Function, Function('console.log(this)')]);
                                // => [ [Function: Function], [Function] ]
console.log(Error, Error('Some error')]);
                    // => [ { [Function: Error]
                    //        captureStackTrace: [Function: captureStackTrace],
                    //        stackTraceLimit: 10 },
                    //      [Error: Some error] ]

// The Number(), String(), and Boolean() constructors not only construct
// objects; they also provide a primitive value for a string, number and
// boolean, depending upon how the constructor is leveraged. If you called
// these constructors directly, then a complex object is returned. If you
// simply express a number, string, or boolean value in your code (primitive
// values like 5, "foo" and true), then the constructor will return a
// primitive value instead of a complex object value.
