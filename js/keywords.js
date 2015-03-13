var a;                                  // variable declaration
fn = function hw() { return arguments}  // function definition
                                        //  return a list of arguments passed
Number(10);                     // keyword that bakes numeric data-type
String('10');                   //  that bakes string data-type
Boolean(true);                  //  that bakes boolean data-type
Function('console.log(10)')     //  that bakes function data-type
Array(10, 20);                  //  that bakes array-like object
RegExp(10);                     //  that bakes regexp-like object
Date();                         //  that bakes date like object

typeof(a);                      // return a string denoting typeof a
Number(100) instanceof Number;  // => false
(new Number(100)) instanceof Number;    // => true

obj = { 'first-name': 'arun', 'age': 22 };
arr = [10,20]
delete obj['first-name']    // delete the key `first-name` from obj
delete arr[0]               // object or array ??

return;     // return value from function, otherwise function implicitly
            // returns `undefined`.


