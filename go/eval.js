var a = 10;

// expressions can be evaluated, returns the value.
eval('10*20')       // => 200
// assignments can be evaluated, return assigned value.
eval('x=100')       // => 100
// even statements can be evaluated
eval('if(true) { 100 } else {200}') // => 100

function bar(s) {
    var a = 100;
    eval(s);
    setTimeout(function(){a=2000,b=20}, 200);
    setTimeout(function(){console.log(a)}, 300);
}

bar('a=1000;');
console.log(a);
setTimeout(function(){console.log([a,b])}, 300);
