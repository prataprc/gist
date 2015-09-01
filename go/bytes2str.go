package main

import "runtime"
import "fmt"
import "unsafe"
import "reflect"

func main() {
	var ms runtime.MemStats
	runtime.ReadMemStats(&ms)
	fmt.Printf("before %+v\n", ms)
	s := try()
	runtime.GC()
	runtime.ReadMemStats(&ms)
	fmt.Printf("after %+v\n", ms)
	fmt.Println(s)
}

func try() string {
	bs := make([]byte, 1024)
	copy(bs, []byte("hello"))
	return bytes2str(bs[:5])
}

func bytes2str(bytes []byte) string {
	if bytes == nil {
		return ""
	}
	sl := (*reflect.SliceHeader)(unsafe.Pointer(&bytes))
	st := &reflect.StringHeader{Data: sl.Data, Len: sl.Len}
	return *(*string)(unsafe.Pointer(st))
}
