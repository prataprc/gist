package main

import "fmt"
import "time"

import "github.com/golang/protobuf/proto"
import protobuf "github.com/couchbase/indexing/secondary/protobuf/data"

func main() {
	var start time.Time
	count := 1000000
	mp := protobuf.KeyVersions{}

	data, _ := Marshal(1000000)

	//start = time.Now()
	//for i := 0; i < count; i++ {
	//	proto.Unmarshal(data, &mp)
	//}
	//fmt.Printf("elapsed: %v\n", time.Since(start))

	decb := proto.NewBuffer(data)
	start = time.Now()
	for i := 0; i < count; i++ {
		decb.Unmarshal(&mp)
	}
	fmt.Printf("elapsed: %v\n", time.Since(start))
}

func Marshal(count int) ([]byte, error) {
	mp := protobuf.KeyVersions{
		Seqno:    proto.Uint64(uint64(10000000)),
		Uuids:    []uint64{0x1234567812345678},
		Commands: []uint32{4},
	}
	mp.Docid = []byte("cities")
	mp.Keys = [][]byte{[]byte("bangalore"), []byte("delhi"), []byte("jaipur")}
	mp.Oldkeys = [][]byte{[]byte("varanasi"), []byte("pune"), []byte("mahe")}
	for i := 0; i < count; i++ {
		proto.Marshal(&mp)
	}
	return proto.Marshal(&mp)
}
