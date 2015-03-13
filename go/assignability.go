package main

import "fmt"

var x int8 = 10

// A value x is assignable to a variable of type T ("x is assignable to T") in
// any of these cases:

// x's type is identical to T.
var r int8 = x

// x's type V and T have identical underlying types and at least one of V or T
// is not a named type.

// T is an interface type and x implements T.

// x is a bidirectional channel value, T is a channel type, x's type V and T
// have identical element types, and at least one of V or T is not a named type.

// x is the predeclared identifier nil and T is a pointer, function, slice,
// map, channel, or interface type.

// x is an untyped constant representable by a value of type T.
// Any value may be assigned to the blank identifier.

type X struct {
	a int
}

func main() {
	var newx X
	m := map[string]X{"x": X{10}}
	newx = m["x"]
	newx.a = 20
	fmt.Println(m["x"], newx)
	fmt.Println(m["x"], passByValue(m["x"]))
	retnewx := returnByValue(&newx)
	fmt.Println(m["x"], retnewx)
	newx.a = 50
	fmt.Println(newx, retnewx)
}

func passByValue(x X) *X {
	x.a = 30
	return &x
}

func returnByValue(x *X) X {
	x.a = 40
	return *x
}
