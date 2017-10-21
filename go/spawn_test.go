package main

import "testing"

func BenchmarkGoroutine(b *testing.B) {
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		ch := make(chan struct{})
		go func() { close(ch) }()
		<-ch
	}
}
