package main

import (
	"fmt"
)

type X struct {
	a int
	b int
}

func main() {
	xm := make(map[*X]bool)
	xs := []X{X{10, 20}, X{20, 30}}
	for _, x := range xs {
		fmt.Printf("%p\n", &x)
		xm[&x] = true
	}
	fmt.Println(len(xm))
}
