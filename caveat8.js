function foo() {
    for(var i = 0; i < 10; i++) {
        setTimeout(function() {
            console.log(i);  
        }, 100);
    }
}
foo();

//----- possible solution
for(var i = 0; i < 10; i++) {
    (function(e) {
        setTimeout(function() { console.log(e);  }, 1000);
    })(i);
}
