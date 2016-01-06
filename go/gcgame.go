package main

import "fmt"
import "unsafe"
import "runtime"

import "reflect"

func main() {
	data := make([]unsafe.Pointer, 100)
	hdr := (*reflect.SliceHeader)(unsafe.Pointer(&data))
	fmt.Printf("allocated data.SliceHeader @ {%p,%p} -> block @ %p\n", &data, hdr, hdr.Data)
	block := unsafe.Pointer(hdr.Data)
	fmt.Printf("reference to data.Block %p\n", block)

	for i := int64(0); i < 100; i++ {
		x := new(int64)
		*x = i
		data[i] = unsafe.Pointer(x)
		fmt.Printf("original %v %p\n", i, data[i])
	}

	hdr = nil
	data = nil

	runtime.GC()

	//	newhdr := new(reflect.SliceHeader)
	var newhdr reflect.SliceHeader
	newhdr.Data = uintptr(block)
	newhdr.Len = 100
	newhdr.Cap = 100

	data = *((*[]unsafe.Pointer)(unsafe.Pointer(&newhdr)))

	for i := 0; i < 100; i++ {
		fmt.Printf("%v \n", *((*int)(data[i])))
	}
}
