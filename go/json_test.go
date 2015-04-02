package jsonbench

import "testing"
import "encoding/json"

func BenchmarkString(b *testing.B) {
	s := "hello world"
	for i := 0; i < b.N; i++ {
		json.Marshal(s)
	}
}
