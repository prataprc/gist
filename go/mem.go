package main

import "fmt"
import "bytes"

func main() {
	fmt.Println(bytes.Compare([]byte("hello"), nil))
	fmt.Println(bytes.Compare(nil, []byte("hello")))
}
