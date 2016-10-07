package main

import "fmt"
import "unsafe"
import "reflect"

//#include <stdlib.h>
import "C"

func main() {
	var s string
	var i int
	ss := (*reflect.StringHeader)(unsafe.Pointer(&s))
	fmt.Printf("pointsto:%v, len:%v\n", ss.Data, ss.Len)
	s = "hello"
	ss = (*reflect.StringHeader)(unsafe.Pointer(&s))
	fmt.Printf("i:%p s:%p pointsto:%x, len:%v\n", &i, &s, ss.Data, ss.Len)
	cs := C.CString(s)
	fmt.Printf("cs:%p, %T %v\n", &cs, cs, cs)
	var ptr *C.char
	fmt.Printf("%v", &ptr)
}
