package mem

import "testing"
import "strconv"

func BenchmarkSinglePrecision(b *testing.B) {
	acc := float32(0)
	for i := 0; i < b.N; i++ {
		acc += float32(2.2)
	}
}

func BenchmarkDoublePrecision(b *testing.B) {
	acc := float64(0)
	for i := 0; i < b.N; i++ {
		acc += float64(2.2222222222)
	}
}

func BenchmarkParseFloat(b *testing.B) {
	for i := 0; i < b.N; i++ {
		strconv.ParseFloat("10.312341243532534", 64)
	}
}
