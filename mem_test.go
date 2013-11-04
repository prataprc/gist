package main

import (
    "testing"
)

var count int
func Benchmark_memcpy(b *testing.B) {
    var src [1024*1024*1]byte
    for i := 0; i < len(src); i++ {
        src[i] = byte(i)
    }
    b.ResetTimer()
    for i := 0; i < b.N; i++ {
        dst := src
        count += len(dst)
    }
}
