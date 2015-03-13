package main

import (
	"testing"
)

var count int

func BenchmarkAppend(b *testing.B) {
	var src, dst [10 * 1]byte
	for i := 0; i < len(src); i++ {
		src[i] = byte(i)
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		count += len(append(dst[:], src[0:]...))
	}
}

func BenchmarkCopy(b *testing.B) {
	var src, dst [10 * 1]byte
	for i := 0; i < len(src); i++ {
		src[i] = byte(i)
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		copy(dst[:], src[:])
	}
}
