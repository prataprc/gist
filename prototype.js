function Foo() {
    this.value = 42;
    this.id = 'i am foo';
}
Foo.prototype = {               // set Foo's prototype to some property
    foo: function() {}
};

function Bar() {}
Bar.prototype = new Foo();      // set Bar's prototype to an instance of Foo
Bar.prototype.foo = 'Hello World';
Bar.prototype.constructor = Bar; // Bar's constructor

var bar1 = new Bar(); // create a new bar instance
var bar2 = new Bar(); // create a new bar instance

console.log( bar1 );            // => {}
console.log( bar1.prototype );  // => undefined

console.log( Foo.prototype );
console.log( bar1.constructor == Bar )      // => true
console.log( bar1.constructor.prototype );

bar1.constructor.prototype.value = 24;
console.log(bar2.value);    // => 24
bar2.value = 12;
console.log(bar1.value);    // => 24
