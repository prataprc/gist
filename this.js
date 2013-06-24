this;                           // global object
function Foo(a) {
    this.a = a;
    this.update = function(val) { this.val = val };
}

Foo(10);                // `a`, `update` is added to global scope
var x = new Foo(20);    // `a`, `update` is added to `x`, x.a is 20

var bar = {};
Foo.apply(bar, [10]);   // `this` is set to bar
Foo.call(bar, 20)       // same as before except the function signature

x.myfn = function(s) { this.string = s; }
x.myfn('hello');

//---- Late binding of this
var update_alias = x.update;
x.update(100);
update_alias(200);
update_alias.call(this, 300);
console.log([this.val, x.val]);     // => [ undefined, 100 ]
