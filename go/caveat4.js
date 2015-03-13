function foo() { 100 }
console.log( foo() == undefined ) // => true
var undefined=23;
console.log( foo() == undefined ) // => false
