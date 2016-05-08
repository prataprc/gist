package main

import "fmt"

func main() {
	buf := make([]byte, 0, 6)
	for i := 0; i < 3; i++ {
		fmt.Printf("iteration %v : buf{%v %v}\n", i, len(buf), cap(buf))
		bs := joinbytes([]byte{1, 2, 3}, buf)
		//l := len(bs)
		//buf = buf[l:l]
		buf = bs
		fmt.Printf("iteration %v : bs{%v,%v} buf{%v,%v}\n", i, len(bs), cap(bs), len(buf), cap(buf))
	}
}

func joinbytes(input, buf []byte) []byte {
	buf = append(buf, input...)
	return buf
}

// iteration 0 : buf{0 6}
// iteration 0 : bs{3,6} buf{0,3}
// iteration 1 : buf{0 3}
// iteration 1 : bs{3,3} buf{0,0}
// iteration 2 : buf{0 0}
// panic: runtime error: slice bounds out of range
