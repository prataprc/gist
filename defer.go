package main

import "fmt"

type X struct {
	a int
}

func main() {
	//ch := make(chan bool, 1)
	//defer func() { printHealthy(<-ch) }()
	//ch <- true
	fn()
}

func printHealthy(healthy bool) {
	fmt.Printf("healthy: %v\n", healthy)
}

func fn() {
	for i := 0; i < 10; i++ {
		x := newX(i)
		defer x.Print()
	}
	return
}

func newX(a int) *X {
	return &X{a}
}

func (x *X) Print() {
	fmt.Printf("%p %v\n", x, x)
}
