package main

import "sync"
import "fmt"

// maximum length of json pointer is restricted to 1024 bytes.
var prefixPool *sync.Pool

func init() {
	prefixPool = &sync.Pool{
		New: func() interface{} {
			return make([]byte, 0, 1024) // TODO: no magic number
		},
	}
}

func main() {
	slice := prefixPool.Get().([]byte)
	fmt.Printf("1s get: cap=%v len=%v\n", cap(slice), len(slice))
	slice = append(slice, 10)
	fmt.Printf("1s append: cap=%v len=%v\n", cap(slice), len(slice))
	prefixPool.Put(slice)

	slice = prefixPool.Get().([]byte)
	fmt.Printf("2s get: cap=%v len=%v\n", cap(slice), len(slice))
	slice = append(slice, 10)
	fmt.Printf("3s append: cap=%v len=%v\n", cap(slice), len(slice))
	prefixPool.Put(slice[:0])
}
