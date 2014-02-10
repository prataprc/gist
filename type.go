package main

import "fmt"

func main() {
	var (
		b  bool // Boolean
		i  int  // Numeric
		c  int8
		hw int16
		w  int32
		lw int64
		f  float32
		d  float64
		s  string // String

		ar  [10]int        // Array
		ars []int          // Slice
		p   *int           // Pointer
		m   map[string]int // Map
		fn  func(int) int  // Function
		inf interface{}    // Interface
		ch  chan int       // Channel
	)

	fmt.Printf("Types \n\n")
	fmt.Printf("int       %T\n", i)
	fmt.Printf("int8      %T\n", c)
	fmt.Printf("int16     %T\n", hw)
	fmt.Printf("int32     %T\n", w)
	fmt.Printf("int64     %T\n", lw)
	fmt.Printf("float32   %T\n", f)
	fmt.Printf("float64   %T\n", d)
	fmt.Printf("string    %T\n", s)
	fmt.Printf("bool      %T\n", b)
	fmt.Printf("array     %T\n", ar)
	fmt.Printf("map       %T\n", m)
	fmt.Printf("pointer   %T\n", p)
	fmt.Printf("function  %T\n", fn)
	fmt.Printf("interface %T\n", inf)
	fmt.Printf("channel   %T\n", ch)

	fmt.Printf("slice     %T\n", ar[1:2])
}
