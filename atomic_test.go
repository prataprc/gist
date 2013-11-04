package main

import (
    "testing"
    "sync/atomic"
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
