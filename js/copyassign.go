package main

import "fmt"

func main() {
	var (
		b  bool    = false // Boolean
		c  int8    = 'a'
		hw uint16  = 0xEFEF
		w  uint32  = 0xDEADBEAF
		lw uint64  = 0xBEAFDEADDEADBEAF
		f  float32 = 10.2
		d  float64 = 20.1
		s  string  = "hello" // String

		ar = [...]int{1, 2, 3} // Array
	)
	xb := b
	xb = true
	fmt.Printf("bool assignment %v %v \n", b, xb)
	xc := c
	xc = 'b'
	fmt.Printf("int8 assignment %v %v \n", c, xc)
	xd := hw
	xd = 0x1
	fmt.Printf("uint16 assignment %v %v \n", hw, xd)
	xe := w
	xe = 0x1
	fmt.Printf("uint32 assignment %v %v \n", w, xe)
	xf := lw
	xf = 0x1
	fmt.Printf("uint64 assignment %v %v \n", lw, xf)
	xg := f
	xg = 0.1
	fmt.Printf("float32 assignment %v %v \n", f, xg)
	xh := d
	xh = 0.1
	fmt.Printf("float64 assignment %v %v \n", d, xh)
	xi := s
	xi = "world"
	fmt.Printf("string assignment %v %v \n", s, xi)
	xj := ar
	xj[0] = 100
	fmt.Printf("float64 assignment %v %v \n", ar, xj)

	m := make(map[string]int) // Map
	m["x"] = 10
	m["y"] = 20
	n := m
	m["x"] = 100
	fmt.Printf("float64 assignment %v %v \n", m, n)

}
