package strconvbench

import "testing"
import "strconv"

func BenchmarkAtoi(b *testing.B) {
	s := "1234567890"
	for i := 0; i < b.N; i++ {
		strconv.Atoi(s)
	}
}

func BenchmarkItoa(b *testing.B) {
	n := 1234567890
	for i := 0; i < b.N; i++ {
		strconv.Itoa(n)
	}
}
