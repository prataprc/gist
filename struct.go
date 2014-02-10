package main

import "fmt"

type X struct {
	xa int
	xb byte
}

type Y struct {
	c string
}
type Z struct {
	c string
}

type N struct {
	X
	nn string
}
type M struct {
	X
	Y
	Z
}

func main() {
	x := X{xa: 10000, xb: 10}
	y := Y{c: "hello"}
	z := Z{c: "world"}
	n := N{X: x, nn: "nstring"}
	m := M{x, y, z}

	fmt.Println(x)
	fmt.Println(y)
	fmt.Println(n, n.xa, x.xb, n.nn)
	fmt.Println(m, m.Y.c)

	var i interface{}
	i = m
	fmt.Println(i.(X))

}
