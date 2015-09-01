package mem

import "testing"
import "strconv"

func BenchmarkParseFloat(b *testing.B) {
	for i := 0; i < b.N; i++ {
		strconv.ParseFloat("10.312341243532534", 64)
	}
}
