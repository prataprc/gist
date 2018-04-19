package main

import (
	"fmt"
	"sync/atomic"
	"unsafe"
)

var x = 10
var m = make(map[string]string)

var keys unsafe.Pointer = unsafe.Pointer(&m)
var y = 20
var s = "hello world"

func main() {
	m["yes"] = "minister"
	m["monty"] = "python"
	fmt.Println(&m, &x, &y, &s)
	fmt.Println(len(m), unsafe.Sizeof(m))

	opp := atomic.LoadPointer(&keys)
	old := (*map[string]string)(opp)
	fmt.Println(&m, keys, opp, old)

	var snapspin uint64
	l := atomic.AddUint64(&snapspin, 1)
	x := atomic.AddUint64(&snapspin, ^uint64(0))
	fmt.Printf("snapspin %x %x\n", l, x)

	snapspin = 0x8000000000000002
	l = atomic.AddUint64(&snapspin, 1)
	x = atomic.AddUint64(&snapspin, ^uint64(0))
	fmt.Printf("snapspin %x %x\n", l, x)

	snapspin = 0xc000000000000001
	l = atomic.AddUint64(&snapspin, 1)
	x = atomic.AddUint64(&snapspin, ^uint64(0))
	fmt.Printf("snapspin %x %x\n", l, x)
}
