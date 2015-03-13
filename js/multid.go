package main

import (
	"fmt"
	"unsafe"
)

func main() {
	var x [2][2]int
	p := unsafe.Pointer(&x[0])
	q := unsafe.Pointer(&x[1])
	fmt.Println(x, x[0], x[1], p, q)
}
