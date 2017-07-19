package mod

import "time"
import "testing"
import _ "fmt"

func BenchmarkModInt64(b *testing.B) {
	ns := int64(time.Now().UnixNano())
	a := int64(0)
	for i := 0; i < b.N; i++ {
		a += (ns % 10)
	}
}

func BenchmarkModUint64(b *testing.B) {
	ns := uint64(time.Now().UnixNano())
	a := uint64(0)
	for i := 0; i < b.N; i++ {
		a += (ns % 10)
	}
}
