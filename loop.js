var num=10;
while(num>6) { num--; }     // while
do { num-- } while(num>35); // do .. while
for(var i; i<num; i++) {    // for
    if(i==1) break;             // to break out of loop
    if(i==3) continue;          // to skip and continue with next iteration
    num++;
}
var foo = { goo: undefined };
for(var property in foo) { };   // iterate over property for object.
