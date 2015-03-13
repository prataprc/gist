package main

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

func main() {
}
