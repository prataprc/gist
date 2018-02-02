package main

import (
	"fmt"
	"hash/crc32"
)

func main() {
	msga := []byte("hello world")
	msgb := []byte("user a")
	msgc := []byte("user b")

	tbl := crc32.MakeTable(crc32.IEEE)
	crc := crc32.Checksum(msga, tbl)
	crc = crc32.Update(crc, tbl, msgb)
	crc = crc32.Update(crc, tbl, msgc)
	fmt.Println(crc)
	crc = crc32.Checksum(msgc, tbl)
	crc = crc32.Update(crc, tbl, msga)
	crc = crc32.Update(crc, tbl, msgb)
	fmt.Println(crc)
}
