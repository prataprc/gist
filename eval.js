var a = 10;

function bar(s) {
    var a = 100;
    eval(s);
    setTimeout(function(){a=2000,b=20}, 200);
    setTimeout(function(){console.log(a)}, 300);
}

bar('a=1000;');
console.log(a);
setTimeout(function(){console.log([a,b])}, 300);
