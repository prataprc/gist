function Foo() {
    this.val = 1;   // this is a new object instance if preceded by ``new``
    // return this;
}
function Bar() {
    this.b = 20;        // ``this`` is lost anyway.
    return {'a' : 10};  // because we are returning a different object.
}
function Mat() {
    this.b = 20;        // ``this`` is not lost
    return 10;          // because we are not returning an object-type.
}

var foo = new Foo();
var bar = new Bar();
var mat = new Mat();
[foo.prototype, Foo.prototype];     // => [ undefined, {} ]
foo;                                // => { val: 1 }
bar;                                // => { a: 10 }
mat;                                // => { b: 20 }
