package main

import "fmt"
import "reflect"
import "unsafe"

func main() {
	a := 10
	s := makestack()
	sl := (*reflect.StringHeader)(unsafe.Pointer(&s))
	fmt.Printf("mainstack %p %p block %x\n", &a, &sl, sl.Data)
	fmt.Printf("maindata %x\n", *(*uint64)(unsafe.Pointer(sl.Data)))
}

func makestack() string {
	x := 10
	s := fmt.Sprintf("abcd")
	sl := (*reflect.StringHeader)(unsafe.Pointer(&s))
	fmt.Printf("makestack %p %p block %x\n", &x, &sl, sl.Data)
	fmt.Printf("makedata %x\n", *(*uint64)(unsafe.Pointer(sl.Data)))
	return s
}
