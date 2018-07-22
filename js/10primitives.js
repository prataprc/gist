var log = require('./lib').log;

var x = 10;             // primitive literal
var y = Number(10);     // object
var z = x.value;        // literal becomes an object and un-becomes again

var getKeys = function(obj){
    var keys = [];
    for(var key in obj){ keys.push(key); }
    return keys;
}
var Person = function(living, age, gender) {
    this.living = living;
    this.age = age;
    this.gender = gender;
    this.getGender = function() {return this.gender;};
};

log(10);
p = new Person();
console.log( Person.constructor )


// what about Date, Array, Function, Error, Object
