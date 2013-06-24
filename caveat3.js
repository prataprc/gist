var count = 0;
function foo(){
    var num = 1000000000;
    console.log("start " + count);
    while(num) { num-- }
    console.log("end " + count);
    count++;
}
setInterval(foo, 10);

// Better style of programming, if we suspect that the handler might take more
// time than the timeout value.
function bar(){
    console.log('I will run as long as it takes');
    setTimeout(bar, 10);
}
setTimeout(bar,1);
