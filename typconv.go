package main

import (
	"fmt"
)

func main() {
	type Bytes []byte
	Bs := Bytes([]byte("hello"))
	bs := []byte(Bs)
	fmt.Println(Bs, bs)
}
