// In 2.toString() 2. interpreted as float and then parser fails !!

2..toString();  // the second point is correctly recognized
2 .toString();  // note the space left to the dot
(2).toString(); // 2 is evaluated first

obj = { 'first-name': 'shiva', 'age': 20 };
obj['first-name'];  // cannot access as obj.first-name
obj.age             // is good.


