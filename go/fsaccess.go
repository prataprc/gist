package main

import (
	"fmt"
	"os"
	"reflect"
	"unsafe"
)

func main() {
	var x int32 = 0x12345678
	var buf []byte
	fd, _ := os.Create("access.dat")
	fd.Write([]byte("hello world this is a long string"))

	bufp := (*reflect.SliceHeader)(unsafe.Pointer(&buf))
	bufp.Data = (uintptr)(unsafe.Pointer(&x))
	bufp.Len = 4
	bufp.Cap = 4
	fmt.Println(bufp, buf)
	os.Remove("access.dat")
}
