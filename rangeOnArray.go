package main

import (
	"fmt"
)

type X struct {
	a int
	b int
}

func main() {
	var xs [4]X
	ym := make(map[*X]int)
	var x X
	for i := 0; i < len(xs); i++ {
		x = xs[i]
		ym[&x] = 100
		fmt.Printf("%p %p\n", &x, &xs[i])
	}
	fmt.Println(ym)
}
