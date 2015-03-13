package main

import (
	"fmt"
	"unsafe"
)

func main() {
	var sl = []byte{1, 2, 3, 4, 5, 6}
	var cl = []byte{1, 2, 3, 4, 5, 6}

	copyCheck()
	fmt.Println(sl[6:], len(sl[:0]), cap(sl[:0]))
	fmt.Println(unsafe.Pointer(&sl), len(sl), cap(sl))
	sl_ := sl[2:4]
	fmt.Println(unsafe.Pointer(&sl_), len(sl_), cap(sl_))

	copy(sl[2:3], cl[1:4]) // Shift existing data out of the way
	fmt.Println(cap(sl), len(sl), sl)

	fmt.Println("How the capacity varies")
	sl = []byte{1, 2, 3, 4, 5, 6}
	fmt.Println(cap(sl), cap(sl[:2]), cap(sl[2:]))

	fmt.Println("Does append vary the capacity of slice")
	sll := append(sl[:2], 0)
	fmt.Println(sll, len(sll), cap(sll), cap(sl))
	sll = append(sl, 0)
	fmt.Println(len(sll), cap(sll), cap(sl), sl)
	fmt.Println(append(sl[:len(sl)-1], []byte{100, 200}...))
}

func copyCheck() {
	dst := make([]byte, 100, 10)
	src := []byte("123456789012")
	copy(dst, src)
	fmt.Printf("copyCheck (%s) len: %d cap: %d\n", string(dst), len(dst), cap(dst))
}
