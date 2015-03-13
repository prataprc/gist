var a;                      // global

fn = function helloworld() {
    var s = 'string literal local to hello world';
    var t = 'string literal local to hello world';
    sGlobal = 'create a global variable';
    f = function nested() {
        var bn = 'local to nested function';
        var t = 'shadows `t` from `helloworld` closure';
        s = 20; // updates `s` from `helloworld` closure
        console.log(s);
    }
    f();
    console.log(s);
}

fn();
