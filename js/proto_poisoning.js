// Poisoning Object.prototype
Object.prototype.bar = 1;
var foo = { goo: undefined };
console.log([ foo.bar, 'bar' in foo ]); // => [1, true]
console.log([ foo.hasOwnProperty('bar'), foo.hasOwnProperty('goo') ]);
                                        // => [false, true]
