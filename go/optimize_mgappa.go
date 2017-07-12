package main

import "fmt"

//import "math"
import "testing"

func main() {
	fmt.Println(modlongform(10, 4))
	fmt.Println(modshortform(10, 4))
}

func modlongform(c, d int) int {
	e := c / 2
	f := d / 2
	result := e % f
	return result
}

func modshortform(c, d int) int {
	return (c / 2) % (d / 2)
}

func BenchmarkLong(b *testing.B) {
	for i := 0; i < b.N; i++ {
		modlongform(10, 4)
	}
}

func BenchmarkShort(b *testing.B) {
	for i := 0; i < b.N; i++ {
		modshortform(10, 4)
	}
}
