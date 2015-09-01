package mem

import "testing"
import "encoding/binary"
import "bytes"
import "math"

var count int

func BenchmarkMemcpy1K(b *testing.B) {
	var dst, src [1024 * 1]byte
	for i := 0; i < len(src); i++ {
		src[i] = byte(i)
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		copy(dst[:], src[:])
	}
}

func BenchmarkMemcpy4K(b *testing.B) {
	var dst, src [1024 * 4]byte
	for i := 0; i < len(src); i++ {
		src[i] = byte(i)
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		copy(dst[:], src[:])
	}
}

func BenchmarkMemcmp1K(b *testing.B) {
	var src, dst [1024 * 1]byte
	for i := 0; i < len(src); i++ {
		src[i] = byte(i)
		dst[i] = byte(i)
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		bytes.Compare(dst[:], src[:])
	}
}

func BenchmarkBinaryWrite(b *testing.B) {
	buf := make([]byte, 64)
	iobuf := bytes.NewBuffer(buf[:0])
	for i := 0; i < b.N; i++ {
		binary.Write(iobuf, binary.BigEndian, float32(10.2))
	}
}

func BenchmarkFloat32Bits(b *testing.B) {
	for i := 0; i < b.N; i++ {
		math.Float32bits(float32(10.2))
	}
}

func BenchmarkFloat32fromBits(b *testing.B) {
	f := math.Float32bits(float32(10.2))
	for i := 0; i < b.N; i++ {
		math.Float32frombits(f)
	}
}
