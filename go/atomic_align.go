package main

import "sync/atomic"

type X struct {
	a       uint64 // will be 64-bit aligned, no panic
	b       bool
	c       uint64 // will cause panic in 32-bit machine
	d       bool
	e       *uint64 // won't cause panic, if new(uint64) is 64 bit algined
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

func alignedCall(m map[string]uint64, i int, counters [257]uint64) uint64 {
	v := atomic.LoadUint64(&counters[i]) // Will counters be 64-bit aligned
	return v
}

func main() {
	s := X{}

	atomic.AddUint64(&s.a, 1)   // no panic
	//atomic.AddUint64(&s.c, 1) // panic on 32-bit machine
	s.e = new(uint64)           // on 32-bit mach, will it be 64-bit aligned ??
	atomic.AddUint64(s.e, 1)    // no panic, if 64-bit aligned
	// atomic.AddUint64(&s.unalign.j, 1) // panic on 32-bit machine
	atomic.AddUint64(&s.align.m, 1) // no panic
	//atomic.AddUint64(&s.align.o, 1) // panic on 32-bit machine
	m := map[string]uint64{"a": 10}
	counters := [257]uint64{}
	alignedCall(m, 10, counters)
}
