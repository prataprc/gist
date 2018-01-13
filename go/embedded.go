package main

import "fmt"
import "unsafe"

type E struct {
	e1 int64
	e2 int64
}

type A struct {
	E
	s string
}

type B struct {
	E
	b bool
}

func main() {
	var a A
	var b B
	var x, y unsafe.Pointer

	a.E.e1, a.E.e2 = 10, 20
	b.E = a.E

	fmt.Printf("a %#v\n", a)
	fmt.Printf("b %#v\n", b)
}
