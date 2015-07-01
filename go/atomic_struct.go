package main

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
