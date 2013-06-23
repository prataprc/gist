// hasOwnProperty : accidental overriding of thrid-party object
var foo = {
    hasOwnProperty: function() { return false; },
    bar: 'Here be dragons'
};
foo.hasOwnProperty('bar'); // => always false

// Use another Object's hasOwnProperty and call it with 'this' set to foo
({}).hasOwnProperty.call(foo, 'bar'); // true

// It's also possible to use the hasOwnProperty property from the Object
// property for this purpose
Object.prototype.hasOwnProperty.call(foo, 'bar'); // true

