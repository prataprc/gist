package jsonbench

import "bytes"
import "testing"
import "reflect"
import "unsafe"
import "encoding/json"

func BenchmarkMarshalStr(b *testing.B) {
	inp := "hello world"
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		_, err := json.Marshal(inp)
		if err != nil {
			b.Fatal(err)
		}
	}
}

func BenchmarkUnmarshalStr(b *testing.B) {
	jsonstr, err := json.Marshal("hello world")
	if err != nil {
		b.Fatal(err)
	}
	b.ResetTimer()
	var out string
	for i := 0; i < b.N; i++ {
		err := json.Unmarshal(jsonstr, &out)
		if err != nil {
			b.Fatal(err)
		}
	}
}

func BenchmarkEncodeStr(b *testing.B) {
	inp := interface{}("hello world")
	buf := bytes.NewBuffer(make([]byte, 0, 100))
	enc := json.NewEncoder(buf)
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		enc.Encode(inp)
		buf.Reset()
	}
}

func BenchmarkDecodeStr(b *testing.B) {
	buf := bytes.NewBuffer(make([]byte, 0, 10000))
	json.NewEncoder(buf).Encode("hello world")
	jsonstr := buf.Bytes()
	outstr := bytes2str(make([]byte, 0, 10000))
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		err := json.Unmarshal(jsonstr, &outstr)
		if err != nil {
			b.Fatal(err)
		}
	}
}

func bytes2str(bytes []byte) string {
	if bytes == nil {
		return ""
	}
	sl := (*reflect.SliceHeader)(unsafe.Pointer(&bytes))
	st := &reflect.StringHeader{Data: sl.Data, Len: sl.Len}
	return *(*string)(unsafe.Pointer(st))
}
