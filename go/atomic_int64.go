package main

import "fmt"
import "sync/atomic"

type X struct {
	z uint64
	a chan bool
	b chan bool
	c *int64
	d string
	e uint64
}

func main() {
	s := X{}
	fmt.Println(s.z)
	atomic.AddUint64(&s.z, 1)
	fmt.Println(s.z)
	fmt.Println(s.e)
	atomic.AddUint64(&s.e, 1)
	fmt.Println(s.e)
}
