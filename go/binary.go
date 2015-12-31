package main

import "encoding/binary"
import "fmt"

func main() {
	buf := make([]byte, 8)
	binary.BigEndian.PutUint64(buf, 0x12345678DEADBEAF)
	fmt.Println(buf)
	binary.LittleEndian.PutUint64(buf, 0x12345678DEADBEAF)
	fmt.Println(buf)
}
