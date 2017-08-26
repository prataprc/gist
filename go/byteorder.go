package main

import "fmt"
import "unsafe"
import "reflect"
import "sync/atomic"
import "io/ioutil"

func main() {
	atomicorder()
}

func atomicorder() {
	b := make([]byte, 8)
	switch whatendian() {
	case "little":
		atomicstore(b, 0x1234567890abcdef)
		if err := ioutil.WriteFile("order.bin", b, 0664); err != nil {
			panic(err)
		}

	case "big":
		data, err := ioutil.ReadFile("order.bin")
		if err != nil {
			panic(err)
		}
		fmt.Println(atomicload(data))
	}
}

func atomicload(buf []byte) uint64 {
	sl := (*reflect.SliceHeader)(unsafe.Pointer(&buf))
	return atomic.LoadUint64((*uint64)(unsafe.Pointer(sl.Data)))
}

func atomicstore(buf []byte, value uint64) {
	sl := (*reflect.SliceHeader)(unsafe.Pointer(&buf))
	atomic.StoreUint64((*uint64)(unsafe.Pointer(sl.Data)), value)
}

func whatendian() string {
	var buf []byte
	sl := (*reflect.SliceHeader)(unsafe.Pointer(&buf))
	val := uint64(0x1234567890abcdef)
	sl.Data = (uintptr)(unsafe.Pointer(&val))
	sl.Len, sl.Cap = 8, 8
	if buf[0] == 0xef {
		return "little"
	}
	return "big"
}
