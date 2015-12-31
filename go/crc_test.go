package main

import "hash/crc32"
import "testing"

func BenchmarkCrc32Small(b *testing.B) {
	var data = make([]byte, 1*128)
	for i := 0; i < len(data); i++ {
		data[i] = byte(i)
	}
	tbl := crc32.MakeTable(crc32.IEEE)
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		crc32.Checksum(data, tbl)
	}
}

func BenchmarkCrc32Medium(b *testing.B) {
	var data = make([]byte, 1*512)
	for i := 0; i < len(data); i++ {
		data[i] = byte(i)
	}
	tbl := crc32.MakeTable(crc32.IEEE)
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		crc32.Checksum(data, tbl)
	}
}

func BenchmarkCrc32Large(b *testing.B) {
	var data = make([]byte, 1*1024*1024)
	for i := 0; i < len(data); i++ {
		data[i] = byte(i)
	}
	tbl := crc32.MakeTable(crc32.IEEE)
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		crc32.Checksum(data, tbl)
	}
}
