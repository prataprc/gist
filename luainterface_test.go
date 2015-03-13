package perf

import "testing"

type tValue struct {
	tt  byte
	val interface{}
}

func BenchmarkAsStruct(b *testing.B) {
	obj := &tValue{tt: 1, val: float64(10.2)}
	acc := float64(0)
	for i := 0; i < b.N; i++ {
		if obj.tt == 1 {
			acc += obj.val.(float64)
		}
	}
}

func BenchmarkAsInterface(b *testing.B) {
	obj := interface{}(float64(10.2))
	acc := float64(0)
	for i := 0; i < b.N; i++ {
		if x, ok := obj.(float64); ok {
			acc += x
		}
	}
}
