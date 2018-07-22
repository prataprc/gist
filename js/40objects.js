// An object is just a container for a collection of named values
// (aka properties).
var obj = new Object();
obj.name = 'pratap';
obj.age = 16;
obj.gender = 'male';

//In JS methods are properties that contain a Function() object.
obj.getGender = function() { return obj.gender; }

var myObject = new Object(); // produces an Object() object
obj['0'] = 'f';
obj['1'] = 'o';
obj['2'] = 'o';
console.log(obj);       // output => { 0="f", 1="o", 2="o"}
console.log(obj.getGender());

// define Person constructor function in order to create custom Person()
// objects later
var Person = function(living, age, gender) {
    this.living = living;
    this.age = age;
    this.gender = gender;
    this.getGender = function() {return this.gender;};
};
var p = new Person(true, 16, 'male');
console.log(p);
var p = Person(true, 16, 'male');
console.log(typeof(Person));

// One tricky thing about constructor functions is the use the this value inside
// of the function. Remember, a constructor function is just a cookie cutter.
// When used with the new keyword, it will create an object with properties and
// values defined inside of the constructor function. When new is used the
// value this literally means the new object/instance that will be created
// based on the statements inside the constructor function. On the other hand,
// if you create a constructor function and call it without the use of the new
// keyword the this value will refer to the "parent" object that contains the
// function.
