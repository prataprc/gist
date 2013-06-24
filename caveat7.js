function Foo() {
    this.update = function(x, y) {
        that = this;
        function test() {
            this.a = x; // ``this`` refers to global object.
            that.b = y; // refers to Foo() instance.
        }
        test();
    }
};

x = new Foo();
x.update(100, 200);
console.log([x.a, x.b, a]); // => [ undefined, 200, 100 ]
