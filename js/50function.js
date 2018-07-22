var fnA = function(a) { console.log(a) };
var fnB = Function('console.log(10)');

console.log([fnA, fnB]);
fnA(10);
fnB();
