package main

import (
	"fmt"
	"hash/crc32"
	"time"
)

func main() {
	var data = make([]byte, 8*1024)
	for i := 0; i < len(data); i++ {
		data[i] = byte(i)
	}
	tbl := crc32.MakeTable(crc32.IEEE)
	fmt.Println(time.Now())
	crc := crc32.Checksum(data, tbl)
	for i := 0; i < 100000; i++ {
		crc = crc32.Update(crc, tbl, data)
	}
	fmt.Println(time.Now())
}
