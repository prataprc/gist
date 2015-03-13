package main

import (
	"code.google.com/p/goprotobuf/proto"
	"github.com/couchbase/indexing/secondary/protobuf"
)

func main() {
	data, _ := Marshal(1000000)
	Unmarshal(data, 1000000)
}

func Marshal(count int) ([]byte, error) {
	mp := protobuf.Mutation{
		Version: proto.Uint32(uint32(1)),
		Command: proto.Uint32(uint32(1)),
		Vbucket: proto.Uint32(uint32(512)),
		Vbuuid:  proto.Uint64(uint64(0x1234567812345678)),
		Seqno:   proto.Uint64(uint64(10000000)),
	}
	mp.Docid = []byte("cities")
	mp.Keys = [][]byte{[]byte("bangalore"), []byte("delhi"), []byte("jaipur")}
	mp.Oldkeys = [][]byte{[]byte("varanasi"), []byte("pune"), []byte("mahe")}
	mp.Indexids = []uint32{1, 2, 3}
	for i := 0; i < count; i++ {
		proto.Marshal(&mp)
	}
	return proto.Marshal(&mp)
}

func Unmarshal(data []byte, count int) {
	mp := protobuf.Mutation{}
	for i := 0; i < count; i++ {
		proto.Unmarshal(data, &mp)
	}
}
