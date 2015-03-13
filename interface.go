package main

import "fmt"
import "unsafe"
import "reflect"

var bytes = make([]byte, 16, 16)

func main() {
	var a, b, c, d, e interface{}
	var str = "hello world how are u"
	var fl = 0.01
	var tru = true
	var fal = false
	s := str
	a = uint64(0xFFFFFFFFFFFFFFFF)
	b = s
	c = fl
	d = tru
	e = fal
	ps := []unsafe.Pointer{
		unsafe.Pointer(&a),
		unsafe.Pointer(&b),
		unsafe.Pointer(&c),
		unsafe.Pointer(&d),
		unsafe.Pointer(&e),
	}
	fmt.Printf("%p, %p, %p, %p, %p \n", &a, &b, &c, &d, &e)
	fmt.Printf("str %p \n", &str)
	for _, p := range ps {
		b := (*reflect.SliceHeader)(unsafe.Pointer(&bytes))
		b.Data = uintptr(p)
		fmt.Printf("%v \n", bytes)
	}
}
