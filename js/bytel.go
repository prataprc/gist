package main

import (
	"bytes"
	"fmt"
)

func main() {
	barr := []byte("0.000")
	for _, bs := range bytes.Split(barr, []byte{46}) {
		fmt.Println(string(bs))
	}
}
