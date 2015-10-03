package main

import (
	"sync/atomic"
	"testing"
	"unsafe"
)

var count int

func Benchmark_loadpointer(b *testing.B) {
	var val int32
	valp := unsafe.Pointer(&val)

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		atomic.LoadPointer(&valp)
	}
}

func Benchmark_Addint64(b *testing.B) {
	var x int64
	for i := 0; i < b.N; i++ {
		atomic.AddInt64(&x, 1)
	}
}
