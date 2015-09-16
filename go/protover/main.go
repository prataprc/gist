package main

import "fmt"
import "github.com/golang/protobuf/proto"

import v1 "./v1"
import v2 "./v2"

func main() {
	buf := make([]byte, 0, 1024)
	p := proto.NewBuffer(buf)

	// Encode v1.A2B
	sendmsg1 := v1.A2B{Field1: proto.Uint64(10), Field2: proto.Uint64(20)}
	if err := p.Marshal(&sendmsg1); err != nil {
		panic(err)
	}
	data := p.Bytes()
	// Decode as v2.A2BRequired
	rcvmsg1 := v2.A2BRequired{}
	err := proto.Unmarshal(data, &rcvmsg1)
	fmt.Println("Encode with v1.A2B")
	fmt.Println("Decode with v2.A2BRequired")
	fmt.Printf("    : %v\n", err)

	// Encode v2.A2BRequired
	p.Reset()
	sendmsg2 := v2.A2BRequired{Field1: proto.Uint64(10), Field3: proto.Uint64(20)}
	if err := p.Marshal(&sendmsg2); err != nil {
		panic(err)
	}
	// Decode as v1.A2B
	rcvmsg2 := v1.A2B{}
	err = proto.Unmarshal(data, &rcvmsg2)
	fmt.Println("Encode with v2.A2BRequired")
	fmt.Println("Decode with v1.A2B")
	fmt.Printf("    : %v\n", err)

	// Encode v1.A2B
	sendmsg3 := v1.A2B{Field1: proto.Uint64(10), Field2: proto.Uint64(20)}
	if err := p.Marshal(&sendmsg3); err != nil {
		panic(err)
	}
	data = p.Bytes()
	// Decode as v2.A2BOptional
	rcvmsg3 := v2.A2BOptional{}
	err = proto.Unmarshal(data, &rcvmsg3)
	fmt.Println("Encode with v1.A2B")
	fmt.Println("Decode with v2.A2BOptional")
	fmt.Printf("    : %v\n", err)

	// Encode v2.A2BOptional
	p.Reset()
	sendmsg4 := v2.A2BOptional{Field1: proto.Uint64(10), Field3: proto.Uint64(20)}
	if err := p.Marshal(&sendmsg4); err != nil {
		panic(err)
	}
	// Decode as v1.A2B
	rcvmsg4 := v1.A2B{}
	err = proto.Unmarshal(data, &rcvmsg4)
	fmt.Println("Encode with v2.A2BOptional")
	fmt.Println("Decode with v1.A2B")
	fmt.Printf("    : %v\n", err)
}
