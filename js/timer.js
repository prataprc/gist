Bar = function() {
        function foo() { this.a = 100 };
        setTimeout(foo, 10);
      }
b = new Bar();
console.log(a);     // ReferenceError, timeout is not yet fired.

