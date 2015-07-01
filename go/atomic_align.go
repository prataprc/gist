package main

import "sync/atomic"
import "fmt"

type Y struct {
	j uint64 // will cause panic in 32-bit machine
}

type X struct {
	a       uint64 // will be 64-bit aligned, no panic
	b       bool
	unalign Y
}

func y_loaduint64(y *Y) uint64 {
	return atomic.LoadUint64(&y.j)
}

func main() {
	x := X{unalign: Y{10}}

	fmt.Printf("{%p %p %p %p %v}\n", &x, &x.b, &x.unalign, &(x.unalign.j), y_loaduint64(&(x.unalign)))
}
