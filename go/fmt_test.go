package main

import "fmt"
import "testing"

func BenchmarkFmt(b *testing.B) {
	for i := 0; i < b.N; i++ {
		fmt.Sprintf("<ud>%s</ud>", i)
	}
}
