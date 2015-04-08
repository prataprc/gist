package main

import "sync/atomic"
import "fmt"
import "unsafe"

type X struct {
	a       uint64 // will be 64-bit aligned, no panic
	b       bool
	c       uint64 // will cause panic in 32-bit machine
	d       bool
	e       *uint64 // won't cause panic if allocated using new(uint64)
	f       bool
	g       unsafe.Pointer // won't case panic if allocated using new(uint64)
	unalign struct {
		j uint64 // will cause panic in 32-bit machine
	}
	align struct {
		_ uint32
		m uint64 // will be 64-bit aligned, no panic
		n bool
		o uint64 // will cause panic in 32-bit machine
	}
}

// arguments are always 64-bit aligned in stack.
func alignedCall(b bool, i uint64) uint64 {
	v := atomic.LoadUint64(&i)
	fmt.Printf("alignedCall(%p, %p)\n", &b, &i)
	return v
}

func main() {
	s := X{}

	atomic.AddUint64(&s.a, 1) // no panic
	//atomic.AddUint64(&s.c, 1) // panic on 32-bit machine
	s.e = new(uint64)        // on 32-bit mach, will it be 64-bit aligned ??
	atomic.AddUint64(s.e, 1) // no panic, if 64-bit aligned
	s.g = unsafe.Pointer(new(uint64))
	atomic.AddUint64((*uint64)(s.g), 1)
	// atomic.AddUint64(&s.unalign.j, 1) // panic on 32-bit machine
	atomic.AddUint64(&s.align.m, 1) // no panic
	//atomic.AddUint64(&s.align.o, 1) // panic on 32-bit machine
	y := uint64(10)
	x := alignedCall(true, y)
	fmt.Printf("%p: %v\n", &y, y)
	fmt.Printf("%p: %v\n", &x, x)
}
